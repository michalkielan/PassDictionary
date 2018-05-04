#include "anujsonparser.h"

#include <QJsonObject>
#include <QVariantMap>
#include <QJsonArray>

AnuJsonParser::AnuJsonParser(const QByteArray& json) :
  doc{QJsonDocument::fromJson(json)}
{
}

AnuJsonParser::AnuJsonParser(const AnuJsonParser& other) :
  doc{other.doc}
{
}

AnuJsonParser::AnuJsonParser(AnuJsonParser&& other) :
  doc{qMove(other.doc)}
{
}

AnuJsonParser& AnuJsonParser::operator=(const AnuJsonParser& other)
{
  doc = other.doc;
  return *this;
}

AnuJsonParser& AnuJsonParser::operator=(AnuJsonParser&& other)
{
  doc = qMove(other.doc);
  return *this;
}

QVector<uchar> AnuJsonParser::getRandom() const
{
  const QJsonObject jsonObject = doc.object();
  const QVariantMap anuJson = jsonObject.toVariantMap();

  if(anuJson["success"] != "true")
  {
    return {};
  }

  const int length = anuJson["length"].toInt();
  if(length <= 0)
  {
    return {};
  }

  QVector<uchar> rand;
  rand.reserve(length);

  const QJsonArray randomData = jsonObject["data"].toArray();

  for(const auto& value : randomData)
  {
    const uchar randomValue = static_cast<uchar>(value.toDouble());
    rand.push_back(randomValue);
  }

  return rand;
}


AnuJsonParser::~AnuJsonParser()
{
}
