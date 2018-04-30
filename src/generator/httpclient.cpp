#include "generator/httpclient.h"
#include "generator/httpstatuscodes.h"

#include <QList>
#include <QSslError>
#include <QDebug>

HttpClient::HttpClient(const QVector<QString>& _downloadUrls) :
  manager{},
  currentDownloads{},
  isFinished{false},
  downloadedData{},
  downloadUrls{_downloadUrls}
{
  connect(&manager, SIGNAL(finished(QNetworkReply*)), SLOT(downloadFinished(QNetworkReply*)));
}

QVector<QString> HttpClient::getData() const
{
  return getData(5000);
}

QVector<QString> HttpClient::getData(const int timeout_msec) const
{
  QTimer timer;
  timer.setSingleShot(true);
  QEventLoop loop;
  connect(this, SIGNAL(downloadFinished()), &loop, SLOT(quit()));
  connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
  timer.start(timeout_msec);
  loop.exec();

  return downloadedData;
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
        fprintf(stderr, "SSL error: %s\n", qPrintable(error.errorString()));
#else
    Q_UNUSED(sslErrors);
#endif
}

void HttpClient::downloadFinished(QNetworkReply* reply)
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
      downloadedData.push_back(data);
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
