#include "generator/passwriter.h"
#include "generator/anujsonparser.h"
#include "generator/randomcharacters.h"
#include "safequeue.h"

#include <QTextStream>
#include <QByteArray>

PassWriter::PassWriter(const QString _words,
                       const QString _pass,
                       SafeQueue<QByteArray>& _randomData,
                       const CharactersConfig _charactersConfig,
                       QObject* parent) :
  QThread{parent},
  words{qMove(_words)},
  pass{qMove(_pass)},
  randomData{_randomData},
  charactersConfig{_charactersConfig}
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

    RandomCharacters randomCharacters{charactersConfig};

    while(!wordsBuffer.atEnd())
    {
      const QString word = wordsBuffer.readLine();
      const QByteArray anuJson = randomData.pop();

      AnuJsonParser anuJsonParser{anuJson};
      const auto randomBytes = anuJsonParser.getRandom();
      const QString passphrase = randomCharacters.getRandomString(randomBytes);

      passBuffer << passphrase << "\t" << word << "\n";
    }
    pass.close();
    words.close();
  }
  emit writeFinished();
}

PassWriter::~PassWriter()
{
}

