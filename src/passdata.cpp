#include "passdata.h"

#include <QDebug>

PassData::PassData()
{
}

void PassData::addPass(const Passphrase passphrase)
{
  passphrases[passphrase.word] = passphrase.pass;
}

QString PassData::getPass(const QString word)
{
  return passphrases[word];
}

QString PassData::getString()
{
  for(auto& passphrase : passphrases.keys())
  {
    const QString& pass = passphrase;
    const QString& word = passphrases.value(passphrase);
    qDebug() << pass << ", " << word << '\n';
  }
  return "";
}

void PassData::clear()
{
  passphrases.clear();
}
