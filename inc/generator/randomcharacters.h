#ifndef RANDOMNCHARACTERS_H
#define RANDOMNCHARACTERS_H

#include "generator/charactersconfig.h"

#include <QVector>

/**
 * @brief The RandomCharacters class
 */
class RandomCharacters
{

public:

  /**
   * @brief Constructor
   * @param charactersConfig
   */
  RandomCharacters(const CharactersConfig charactersConfig);

  /**
   * @brief Constructor
   * @param charactersConfig
   * @param vector with custom data
   */
  RandomCharacters(const CharactersConfig charactersConfig, const QVector<uchar>& custom);

  /**
   * @brief Get string with random characters
   * @param randomData
   * @return string with random characters
   */
  QString getRandomString(const QVector<uchar> &randomData);

private:

  /**
   * @brief getRandomCharacter
   * @param random value in range 0x00-0xFF
   * @return random character form characters vector
   */
  uchar getRandomCharacter(const uchar value) const;

  /**
   * @brief generate characters vector
   * @param vector with custom characters
   */
  void fillCharacters(const QVector<uchar>& custom);

  const QVector<uchar> symbols
    {'!','@','#','$','%','^','&','*','(',')','-','+','_','=','?'};
  const QVector<uchar> upperWords
    {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
  const QVector<uchar> lowerWords
    {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
  const QVector<uchar> numbers
    {'0','1','2','3','4','5','6','7','8','9'};
  const QVector<uchar> ambigous
    {'{','}','[',']','(',')','/','\\','\'','\"','`','~',',',';',':','.','<','>'};
  QVector<uchar>       characters;
  CharactersConfig     charactersConfig;
};

#endif // RANDOMNCHARACTERS_H
