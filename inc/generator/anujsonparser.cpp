#include "anujsonparser.h"


AnuJsonParser::AnuJsonParser(const QString& anuPage) :
  doc{QJsonDocument::fromJson(anuPage.toUtf8())}
{
}

QVector<uchar>  AnuJsonParser::deserialize()
{
  QVector<uchar> v;
  return v;
}
