#include "generator/passdictionary.h"
#include "generator/anurandom.h"
#include "generator/anujsonparser.h"

#include <QTextStream>

PassDictionary::PassDictionary(const QString _words, QString _pass) :
  words{_words},
  pass{_pass},
  done{false}
{
}

void PassDictionary::write()
{
  // this may be a thread to write data to file
  pass.open(QIODevice::WriteOnly | QIODevice::Text);

  if(words.open(QIODevice::ReadOnly))
  {
    QTextStream wordsBuffer{&pass};
    QTextStream passBuffer{&pass};

    while(!wordsBuffer.atEnd())
    {
      const QString word = wordsBuffer.readLine();
      const QByteArray page = randomData.pop();

      AnuJsonParser anuJsonParser{page};

      const auto passphrase = anuJsonParser.getRandom();
      (void)passphrase;
      passBuffer << "passphrase" << "\t" << word << "\n";
    }
    pass.close();
    words.close();
    done.store(true);
  }
  emit writeFinished();
}

void PassDictionary::readRandom()
{
  AnuRandom anuRandom{5};
  while(!done.load())
  {
    anuRandom.getRandom(randomData);
  }
  emit readRandomFinished();
}
