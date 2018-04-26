#ifndef PASSDATA_H
#define PASSDATA_H

#include "passphrase.h"

#include <QMap>
#include <QString>

class PassData
{
public:
  PassData();
  void addPass(const Passphrase passphrase);
  QString getPass(const QString word);
  QString getString();
  void clear();

private:
  QMap<QString, QString> passphrases;

};

#endif // PASSDATA_H
