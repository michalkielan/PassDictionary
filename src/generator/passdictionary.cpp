#include "generator/passdictionary.h"

#include <QTextStream>

PassDictionary::PassDictionary(QFile _word, QFile _pass) :
  words{_words},
  pass{_pass}
{
}

QString PassDictionary::getString(QByteArray randomData) const
{
  return QString{randomData};
}

void PassDictionary::writeToPass(SafeQueue<QByteArray>& passphrases)
{
  pass.open(QIODevice::WriteOnly | QIODevice::Text);
  QTextStream passStream(&pass);

  if(words.open(QIODevice::ReadOnly))
  {
    enableWidgets(true);

    QTextStream buffer(&pass);
    while(!buffer.atEnd())
    {
      const QString word = buffer.readLine();
      const QString passphrase = toString(passphrases.pop());
      passStream << passphrase << "\t" << word << "\n";
    }
    pass.close();
  }
}


void PassDictionary::write(const QByteArray value)
{
  randomData = qMove(value);
}
