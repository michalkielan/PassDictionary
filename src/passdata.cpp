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

QString PassData::getPdfHtml()
{
  QString passList;
  for(auto& passphrase : passphrases.keys())
  {
    const QString& word = passphrase;
    const QString& pass = passphrases.value(passphrase);
    passList += "<p style=\"font-size:60%;\">" + pass + "\t" + word + "</p>";
  }
  return passList;
}

void PassData::clear()
{
  passphrases.clear();
}
