#include "generator/passdictionary.h"
#include "generator/anurandom.h"
#include "generator/anujsonparser.h"

#include <QTextStream>

PassDictionary::PassDictionary(const QString _words, QString _pass) :
  randomData{},
  passWriter{_words, _pass, randomData},
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
