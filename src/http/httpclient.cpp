#include "http/httpclient.h"
#include "http/httpstatuscodes.h"

#include <QList>
#include <QSslError>
#include <QDebug>

HttpClient::HttpClient(const QVector<QString>& _downloadUrls) :
  manager{},
  currentDownloads{},
  isFinished{false},
  downloadUrls{_downloadUrls}
{
  connect(&manager, &QNetworkAccessManager::finished, this, &HttpClient::readDownloaded);
}

void HttpClient::waitForDownload(const int timeout_ms) const
{
  QTimer timer;
  QEventLoop loop;

  timer.setSingleShot(true);

  connect(this,   &HttpClient::downloadFinished, &loop, &QEventLoop::quit);
  connect(&timer, &QTimer::timeout,              &loop, &QEventLoop::quit);

  timer.start(timeout_ms);
  loop.exec();
}

void HttpClient::requestDownload(const QUrl& url)
{
  QNetworkRequest request{url};
  QNetworkReply* reply = manager.get(request);

#if QT_CONFIG(ssl)
  connect(reply, SIGNAL(sslErrors(QList<QSslError>)), SLOT(sslErrors(QList<QSslError>)));
#endif

  currentDownloads.append(reply);
}

bool HttpClient::isHttpRedirect(QNetworkReply* reply)
{
  const auto statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
  return statusCode == HttpStatusCodes::Redirections::MovedPermanently  ||
         statusCode == HttpStatusCodes::Redirections::Found             ||
         statusCode == HttpStatusCodes::Redirections::SeeOther          ||
         statusCode == HttpStatusCodes::Redirections::UseProxy          ||
         statusCode == HttpStatusCodes::Redirections::TemporaryRedirect ||
         statusCode == HttpStatusCodes::Redirections::PermanentRedirect ||
         0;
}

void HttpClient::execute()
{
  for(const QString& urlPath : downloadUrls)
  {
    const QUrl url = QUrl::fromEncoded(urlPath.toLocal8Bit());
    requestDownload(url);
  }
}

void HttpClient::sslErrors(const QList<QSslError>& sslErrors)
{
#if QT_CONFIG(ssl)
   for (const QSslError &error : sslErrors)
   {
     qDebug() << "SSL error: " << qPrintable(error.errorString());
   }
#else
    Q_UNUSED(sslErrors);
#endif
}

void HttpClient::readDownloaded(QNetworkReply* reply)
{
  const QUrl url = reply->url();
  if (reply->error())
  {
    qDebug() << "Download of " << url.toEncoded().constData() <<
    " failed: " << qPrintable(reply->errorString());
  }

  else
  {
    if(isHttpRedirect(reply))
    {
      qDebug() << "Request was redirected";
    }

    else
    {
      const QString data = reply->readAll();
      emit downloadEvent(qMove(data));
    }
  }

  currentDownloads.removeAll(reply);
  reply->deleteLater();

  if (currentDownloads.isEmpty())
  {
    isFinished.store(true);
    emit downloadFinished();
    QCoreApplication::instance()->quit();
  }
}
