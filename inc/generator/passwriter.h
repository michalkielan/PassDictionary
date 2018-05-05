#ifndef PASSWRITER_H
#define PASSWRITER_H

#include "safequeue.h"

#include <QThread>
#include <QByteArray>
#include <QFile>

class PassWriter : public QThread
{
  Q_OBJECT
public:
  PassWriter(const QString _words, QString _pass, SafeQueue<QByteArray>& _randomData, QObject* parent = nullptr);

  void run() override;

signals:
  void writeFinished();

private:
  void write();

  QFile                  words;
  QFile                  pass;
  SafeQueue<QByteArray>& randomData;
};

#endif // PASSWRITER_H
