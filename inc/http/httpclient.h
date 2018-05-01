#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QtNetwork>
#include <QVector>
#include <QAtomicInt>

class QSslError;

class HttpClient: public QObject
{
  Q_OBJECT

public:
  HttpClient(const QVector<QString>& _downloadUrls);

  bool waitForDownload(const int timeout_ms) const;

public slots:
  void execute();
  void readDownloaded(QNetworkReply* reply);
  void sslErrors(const QList<QSslError>& errors);

signals:
  void downloadFinished();
  void downloadEvent(const QString data);

private:
  QNetworkAccessManager   manager;
  QVector<QNetworkReply*> currentDownloads;
  QAtomicInt              isFinished;
  QVector<QString>        downloadUrls;

  void requestDownload(const QUrl& url);
  static bool isHttpRedirect(const QNetworkReply* const reply);

};



#endif // HTTPCLIENT_H
