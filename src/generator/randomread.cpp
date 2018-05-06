#include "generator/randomread.h"
#include "generator/anurandom.h"
#include "safequeue.h"

#include <QByteArray>

RandomReader::RandomReader(SafeQueue<QByteArray>& _randomData, QObject* parent) :
  QThread{parent},
  randomData{_randomData}
{
}

void RandomReader::readRand()
{
  AnuRandom anuRandom{5};
  while(1)
  {
    anuRandom.getRandom(randomData);
  }
}

void RandomReader::run()
{
  readRand();
}

