 #ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QtCore>
#include <QtNetwork>
#include <QVector>

class HttpClient: public QObject
{
    Q_OBJECT
    QNetworkAccessManager    manager;
    QVector<QNetworkReply*>  currentDownloads;
    QVector<QString>         urls;

public:
    HttpClient(QVector<QString> _urls);
    void doDownload(const QUrl &url);
    static QString saveFileName(const QUrl &url);
    bool saveToDisk(const QString &filename, QIODevice *data);
    static bool isHttpRedirect(QNetworkReply *reply);
  void download();
public slots:

    void downloadFinished(QNetworkReply *reply);
    void sslErrors(const QList<QSslError> &errors);
};

//int main(int argc, char **argv)
//{
//    QCoreApplication app(argc, argv);

//    DownloadManager manager;
//    QTimer::singleShot(0, &manager, SLOT(execute()));

//    app.exec();
//}


#endif // HTTPCLIENT_H
