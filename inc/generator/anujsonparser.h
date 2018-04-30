#ifndef ANUJSONPARSER_H
#define ANUJSONPARSER_H

#include <QJsonDocument>
#include <QVector>

class AnuJsonParser
{
  QJsonDocument doc;

public:
  AnuJsonParser(const QString& anuPage);

  QVector<uchar> deserialize();
};

#endif // ANUJSONPARSER_H
