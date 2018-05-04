#ifndef ANUJSONPARSER_H
#define ANUJSONPARSER_H

#include <QJsonDocument>
#include <QByteArray>
#include <QVector>

class AnuJsonParser
{
  QJsonDocument doc;

public:

  /**
   * @brief Constructor
   * @param anu jason file as array of bytes
   */
  AnuJsonParser(const QByteArray& json);

  /**
   * @brief Copy constructor
   */
  AnuJsonParser(const AnuJsonParser& other);

  /**
   * @brief Move constructor
   */
  AnuJsonParser(AnuJsonParser&& other);

  /**
   * @brief Copy assignment operator
   */
  AnuJsonParser& operator=(const AnuJsonParser& other);

  /**
   * @brief Move assignment operator
   */
  AnuJsonParser& operator=(AnuJsonParser&& other);

  /**
   * @brief Get random data from deserialized json file
   * @return return array o random characters
   */
  QVector<uchar> getRandom() const;

  /**
   * @brief Destructor
   */
  ~AnuJsonParser();
};

#endif // ANUJSONPARSER_H
