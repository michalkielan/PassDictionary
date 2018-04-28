 #ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QtCore>
#include <QtNetwork>
#include <QVector>

class HttpClient: public QObject
{
    Q_OBJECT
    QNetworkAccessManager    manager;
    QVector<QNetworkReply *> currentDownloads;

//public:
//    HttpClient();
//    void doDownload(const QUrl& url);
//    static QString saveFileName(const QUrl& url);
//    bool saveToDisk(const QString &filename, QIODevice* data);
//    static bool isHttpRedirect(QNetworkReply* reply);

//public slots:
//    void execute();
//    void downloadFinished(QNetworkReply* reply);
//    void sslErrors(const QList<QSslError>& errors);
};

#endif // HTTPCLIENT_H
