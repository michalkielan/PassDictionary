#include "generator/passdictionary.h"

PassDictionary::PassDictionary(const QString _words,
                               const QString _pass,
                               const CharactersConfig charactersConfig) :
  randomData{},
  passWriter{qMove(_words), qMove(_pass), randomData, charactersConfig},
  randomReader{randomData}
{
  connect(&passWriter, &PassWriter::writeFinished, &randomReader, &RandomReader::terminate);
}

void PassDictionary::start()
{
  passWriter.start();
  randomReader.start();
}

void PassDictionary::wait()
{
  passWriter.wait();
  randomReader.wait();
}

PassDictionary::~PassDictionary()
{
}
