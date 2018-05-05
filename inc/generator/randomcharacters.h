#ifndef RANDOMNCHARACTERS_H
#define RANDOMNCHARACTERS_H

#include "generator/charactersconfig.h"

#include <QVector>

class RandomCharacters
{

public:
  RandomCharacters(const CharactersConfig charactersConfig);

  RandomCharacters(const CharactersConfig charactersConfig, const QVector<uchar>& custom);

  QString getRandomString(const QByteArray& randomData);

private:

  uchar getRandomCharacter(const uchar value) const;
  void fillCharacters(const QVector<uchar>& custom);

  const QVector<uchar> symbols    {'!','@','#','$','%','^','&','*','(',')','-','+','_','=','?'};
  const QVector<uchar> upperWords {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
  const QVector<uchar> lowerWords {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
  const QVector<uchar> numbers    {'0','1','2','3','4','5','6','7','8','9'};
  const QVector<uchar> ambigous   {'{','}','[',']','(',')','/','\\','\'','\"','`','~',',',';',':','.','<','>'};
  QVector<uchar>       characters;
  CharactersConfig     charactersConfig;
};

#endif // RANDOMNCHARACTERS_H
