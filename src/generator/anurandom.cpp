#include "generator/anurandom.h"
#include "generator/httpclient.h"

AnuRandom::AnuRandom()
{
  const QString format = "uint8";
  url = "/API/jsonI.php?length=" + QString::number(len) + "&type=" + format;
}

QVector<uchar> AnuRandom::getRandom()
{
  const QString anuServer {"qrng.anu.edu.au"};

  QVector<QString> urls;
  urls.push_back(anuServer + url);
  urls.push_back(anuServer + url);
  urls.push_back(anuServer + url);

  HttpClient anuDownloader(urls);
 // QTimer::singleShot(0, &anuDownloader, SLOT(download()));

  anuDownloader.download();

  QVector<uchar> v;
  return v;
}

AnuRandom::~AnuRandom()
{

}
