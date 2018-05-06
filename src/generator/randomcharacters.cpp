#include "generator/randomcharacters.h"

RandomCharacters::RandomCharacters(const CharactersConfig _charactersConfig) :
  charactersConfig{_charactersConfig}
{
  fillCharacters({});
}

RandomCharacters::RandomCharacters(const CharactersConfig _charactersConfig, const QVector<uchar>& custom) :
  charactersConfig{_charactersConfig}
{
  fillCharacters(custom);
}

void RandomCharacters::fillCharacters(const QVector<uchar>& custom)
{
  if(charactersConfig.upperWords) characters.append(upperWords);
  if(charactersConfig.lowerWords) characters.append(lowerWords);
  if(charactersConfig.numbers)    characters.append(numbers);
  if(charactersConfig.symbols)    characters.append(symbols);
  if(charactersConfig.ambigous)   characters.append(ambigous);
  if(charactersConfig.custom && !custom.empty()) characters.append(custom);
}

QString RandomCharacters::getRandomString(const QVector<uchar> &randomData)
{
  QString random;
  random.reserve(randomData.size());

  for(const auto& randomNumber : randomData)
  {
    random.push_back(getRandomCharacter(randomNumber));
  }
  return random;
}

uchar RandomCharacters::getRandomCharacter(const uchar value) const
{
  constexpr const uchar min = 0;
  //assert(characters.size() < 0xFF);
  const uchar max = characters.size()-1;
  const auto index = value % (max + 1 - min) + min;
  return characters[index];
}


