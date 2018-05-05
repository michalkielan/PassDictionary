#include "generator/passwriter.h"
#include "generator/anujsonparser.h"

#include <QTextStream>

PassWriter::PassWriter(const QString _words, QString _pass, SafeQueue<QByteArray>& _randomData, QObject* parent) :
  QThread{parent},
  words{_words},
  pass{_pass},
  randomData{_randomData}
{
}

void PassWriter::run()
{
  write();
}

void PassWriter::write()
{
  pass.open(QIODevice::WriteOnly | QIODevice::Text);

  if(words.open(QIODevice::ReadOnly))
  {
    QTextStream wordsBuffer{&words};
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
  }
  emit writeFinished();
}

