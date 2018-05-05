#include "generator/randomread.h"
#include "generator/anurandom.h"

RandomReader::RandomReader(SafeQueue<QByteArray>& _randomData, QObject* parent) :
  QThread{parent},
  randomData{_randomData}
{
}

void RandomReader::readRand()
{
  AnuRandom anuRandom{5};
  anuRandom.getRandom(randomData);
  int x;
}

void RandomReader::run()
{
  readRand();
}

