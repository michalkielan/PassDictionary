#include "generator/anurandom.h"
#include "http/httpclient.h"
#include "safequeue.h"

#include <QTimer>

AnuRandom::AnuRandom(const qsizetype _len) :
  len{_len},
  url{"/API/jsonI.php?length=" + QString::number(len) + "&type=uint8"}
{
}

QVector<uchar> AnuRandom::getRandom()
{
  const QString downloadUrl{anuServer + url};
  HttpClient anuDownloader{downloadUrl, 10};

  QTimer::singleShot(0, &anuDownloader, SLOT(execute()));

  QVector<QString> pages;

  SafeQueue<QString> queue;

  connect(&anuDownloader, &HttpClient::downloadEvent, this, [&,this](const QByteArray value){
    // pop to queue?
    queue.push(value);
  });

  anuDownloader.waitForDownload(5000);

  QVector<uchar> v;
  return v;
}

AnuRandom::~AnuRandom()
{

}
