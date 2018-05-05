#include "generator/passdictionary.h"

#include <QTextStream>

PassDictionary::PassDictionary(const QString _words, QString _pass) :
  words{_words},
  pass{_pass}
{
}

QString PassDictionary::getString(QByteArray randomData) const
{
  return QString{randomData};
}

void PassDictionary::write(SafeQueue<QByteArray>& randomData)
{
  // this may be a thread to write data to file
  pass.open(QIODevice::WriteOnly | QIODevice::Text);
  QTextStream passStream(&pass);

  if(words.open(QIODevice::ReadOnly))
  {
    QTextStream buffer{&pass};
    while(!buffer.atEnd())
    {
      const QString word = buffer.readLine();
      const QString passphrase = getString(randomData.pop());
      passStream << passphrase << "\t" << word << "\n";
    }
    pass.close();
  }
}

void PassDictionary::readRandom(SafeQueue<QByteArray>& randomData)
{
  (void)randomData;
  // this may be a thread to read data from anu random
}
