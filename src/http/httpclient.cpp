#include "http/httpclient.h"
#include "http/httpstatuscodes.h"

#include <QSslError>
#include <QDebug>
#include <QEventLoop>
#include <QTimer>
#include <QSharedPointer>

HttpClient::HttpClient(const QString _downloadUrl, const int _threadNum) :
  manager{},
  currentDownloads{},
  isFinished{false},
  downloadUrl{qMove(_downloadUrl)},
  threadNum{_threadNum}
{
  connect(&manager, &QNetworkAccessManager::finished, this, &HttpClient::readDownloaded);
}

bool HttpClient::isTimeouted(const int timeout_ms) const
{
  return waitForDownload(timeout_ms);
}

bool HttpClient::waitForDownload(const int timeout_ms) const
{
  QTimer timer;
  QEventLoop eventLoop;

  timer.setSingleShot(true);

  connect(this,   &HttpClient::downloadFinished, &eventLoop, &QEventLoop::quit);
  connect(&timer, &QTimer::timeout,              &eventLoop, &QEventLoop::quit);

  timer.start(timeout_ms);
  eventLoop.exec();

  return timer.isActive();
}

void HttpClient::requestDownload(const QUrl& url)
{
  const QNetworkRequest request{url};
  QNetworkReply* const reply = manager.get(request);

#if QT_CONFIG(ssl)
  connect(reply, SIGNAL(sslErrors(QList<QSslError>)), SLOT(sslErrors(QList<QSslError>)));
#endif

  currentDownloads.append(reply);
}

bool HttpClient::isHttpRedirect(const QNetworkReply* const reply)
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
  const QUrl url = QUrl::fromEncoded(downloadUrl.toLocal8Bit());
  for(int i=0; i<threadNum; i++)
  {
    requestDownload(url);
  }
}

void HttpClient::sslErrors(const QList<QSslError>& sslErrors)
{
#if QT_CONFIG(ssl)
   for(const QSslError &error : sslErrors)
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
  if(reply->error())
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
      const QByteArray data = reply->readAll();
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
