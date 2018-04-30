#include "generator/httpclient.h"

#include <QList>
#include <QSslError>

HttpClient::HttpClient(QVector<QString> _urls) :
  urls{_urls}
{
  connect(&manager, SIGNAL(finished(QNetworkReply*)), SLOT(downloadFinished(QNetworkReply*)));
}


void HttpClient::doDownload(const QUrl &url)
{
  QNetworkRequest request(url);
  QNetworkReply *reply = manager.get(request);

#if QT_CONFIG(ssl)
  connect(reply, SIGNAL(sslErrors(QList<QSslError>)), SLOT(sslErrors(QList<QSslError>)));
#endif

  currentDownloads.append(reply);
  downloadFinished(reply);

}

QString HttpClient::saveFileName(const QUrl& url)
{
  QString path = url.path();
  QString basename = QFileInfo(path).fileName();

  if (basename.isEmpty())
      basename = "download";

  if (QFile::exists(basename))
  {
    // already exists, don't overwrite
    int i = 0;
    basename += '.';
    while (QFile::exists(basename + QString::number(i)))
        ++i;

    basename += QString::number(i);
  }

  return basename;
}

bool HttpClient::saveToDisk(const QString &filename, QIODevice *data)
{
  QFile file(filename);
  if (!file.open(QIODevice::WriteOnly)) {
      fprintf(stderr, "Could not open %s for writing: %s\n",
              qPrintable(filename),
              qPrintable(file.errorString()));
      return false;
  }

  file.write(data->readAll());
  file.close();

  return true;
}

bool HttpClient::isHttpRedirect(QNetworkReply *reply)
{
  int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
  return statusCode == 301 || statusCode == 302 || statusCode == 303
         || statusCode == 305 || statusCode == 307 || statusCode == 308;
}

void HttpClient::download()
{
  for (const QString &arg : urls)
  {
    QUrl url = QUrl::fromEncoded(arg.toLocal8Bit());
    doDownload(url);
  }
}

void HttpClient::sslErrors(const QList<QSslError> &sslErrors)
{
#if QT_CONFIG(ssl)
    for (const QSslError &error : sslErrors)
        fprintf(stderr, "SSL error: %s\n", qPrintable(error.errorString()));
#else
    Q_UNUSED(sslErrors);
#endif
}

void HttpClient::downloadFinished(QNetworkReply *reply)
{
    QUrl url = reply->url();
    if (reply->error())
    {
      fprintf(stderr, "Download of %s failed: %s\n",
              url.toEncoded().constData(),
              qPrintable(reply->errorString()));
    }
    else
    {
      if (isHttpRedirect(reply))
      {
        fputs("Request was redirected.\n", stderr);
      }

      else
      {
        QString filename = saveFileName(url);
        if (saveToDisk(filename, reply))
        {
          printf("Download of %s succeeded (saved to %s)\n",
                 url.toEncoded().constData(), qPrintable(filename));
        }
      }
    }

    currentDownloads.removeAll(reply);
    reply->deleteLater();

    if (currentDownloads.isEmpty()) {
        // all downloads finished
        QCoreApplication::instance()->quit();
    }
}
