#ifndef PASSDATA_H
#define PASSDATA_H

#include <QMap>
#include <QString>

#include "passphrase.h"

class PassData
{
public:
  PassData();

  void addPass(const Passphrase passphrase);
  QString getPass(const QString word);

private:

  QMap<QString, QString> passphrases;
};

#endif // PASSDATA_H
