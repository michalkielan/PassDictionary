#include "passdata.h"

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
