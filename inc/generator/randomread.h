#ifndef RANDOMREAD_H
#define RANDOMREAD_H

#include "safequeue.h"

#include <QThread>
#include <QByteArray>
#include <QFile>

class RandomReader : public QThread
{
  Q_OBJECT
public:
  RandomReader(SafeQueue<QByteArray>& _randomData, QObject* parent = nullptr);

  void run() override;

public slots:
  void readRand();

private:

  SafeQueue<QByteArray>& randomData;
};

#endif // RANDOMREAD_H
