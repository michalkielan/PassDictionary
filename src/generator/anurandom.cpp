#include "generator/anurandom.h"
#include "http/httpclient.h"
#include "safequeue.h"
#include "generator/anujsonparser.h"

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

  SafeQueue<QByteArray> queue;

  connect(&anuDownloader, &HttpClient::downloadEvent, this, [&,this](const QByteArray value){
    // pop to queue?
    queue.push(value);
  });

  if(!anuDownloader.isTimeouted(10000))
  {
    const QByteArray page = queue.pop();

    AnuJsonParser anuJsonParser{page};
    return anuJsonParser.getRandom();
  }

  else
  {
    qDebug() << "Download error: timeout occurs";
    return {};
  }
}

AnuRandom::~AnuRandom()
{

}
