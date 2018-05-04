#ifndef PASSDICTIONARY_H
#define PASSDICTIONARY_H

#include "safequeue.h"

#include <QFile>

class PassDictionary
{

public:

  PassDictionary(QFile _word, QFile _pass);

  void writeToPass(SafeQueue<QByteArray>& passphrases);

private:

  QString getString(QByteArray randomData) const;

  QFile pass;
  QFile words;
};

#endif // PASSDICTIONARY_H
