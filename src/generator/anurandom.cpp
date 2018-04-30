#include "generator/anurandom.h"
#include "http/httpclient.h"

AnuRandom::AnuRandom(const qsizetype _len) :
  len{_len}
{
  const QString format = "uint8";
  url = "/API/jsonI.php?length=" + QString::number(len) + "&type=" + format;
}

QVector<uchar> AnuRandom::getRandom()
{
  QVector<QString> urls;
  urls.push_back(anuServer + url);
  urls.push_back(anuServer + url);
  urls.push_back(anuServer + url);
  urls.push_back(anuServer + url);
  urls.push_back(anuServer + url);
  urls.push_back(anuServer + url);
  urls.push_back(anuServer + url);

  HttpClient anuDownloader(urls);

  QTimer::singleShot(0, &anuDownloader, SLOT(execute()));

  QVector<QString> pages;
  connect(&anuDownloader, &HttpClient::downloadEvent, this, [&,this](const QString value){
    pages.push_back(qMove(value));

    // write to file?
  });

  anuDownloader.waitForDownload(5000);

  QVector<uchar> v;
  return v;
}

AnuRandom::~AnuRandom()
{

}
