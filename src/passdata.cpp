#include "passdata.h"

PassData::PassData()
{
}

PassData::PassData(const PassData& other) :
  passphrases(other.passphrases)
{
}

PassData::PassData(PassData&& other) :
  passphrases(qMove(other.passphrases))
{
}

PassData& PassData::operator=(const PassData& other)
{
  passphrases = other.passphrases;
  return *this;
}

PassData& PassData::operator=(PassData&& other)
{
  passphrases = qMove(other.passphrases);
  return *this;
}

void PassData::addPass(const Passphrase passphrase)
{
  passphrases[passphrase.word] = passphrase.pass;
}

QString PassData::getPass(const QString word) const
{
  return passphrases[word];
}

QString PassData::getPdfHtml() const
{
  QString passList;
  for(const auto& passphrase : passphrases.keys())
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

PassData::~PassData()
{
}
