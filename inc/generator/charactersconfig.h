#ifndef CHARACTERSCONFIG_H
#define CHARACTERSCONFIG_H

/**
 * @brief The CharactersConfig used for set the type of pass
 */
struct CharactersConfig
{
  bool upperWords;
  bool lowerWords;
  bool numbers;
  bool symbols;
  bool ambigous;
  bool custom;
  int  passphraseLength;
};

#endif // CHARACTERSCONFIG_H
