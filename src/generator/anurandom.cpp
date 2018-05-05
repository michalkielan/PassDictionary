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

void AnuRandom::getRandom(SafeQueue<QByteArray>& randomCharacters)
{
  const QString downloadUrl{anuServer + url};

  constexpr const unsigned int downloadThreads = 15;
  HttpClient anuDownloader{downloadUrl, downloadThreads};

  QTimer::singleShot(0, &anuDownloader, SLOT(execute()));

  connect(&anuDownloader, &HttpClient::downloadEvent, this, [&,this](const QByteArray value){
    randomCharacters.push(value);
  });

  constexpr const unsigned int timeout_ms = 10000;
  if(anuDownloader.isTimeouted(timeout_ms))
  {
    qDebug() << "Download error: timeout occurs";
  }
}

AnuRandom::~AnuRandom()
{
}
