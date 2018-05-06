#ifndef PASSDICTIONARY_H
#define PASSDICTIONARY_H

#include "safequeue.h"
#include "generator/passwriter.h"
#include "generator/randomread.h"

#include <QObject>

/**
 * @brief The PassDictionary class - managing passfile generator
 *       and random data reader using producer consumer pattern
 */
class PassDictionary : public QObject
{
  Q_OBJECT

public:

  /**
   * @brief PassDictionary
   * @param file with words
   * @param file with passphrases
   */
  PassDictionary(const QString _words, const QString _pass,
                 const CharactersConfig charactersConfig);

  /**
   * @brief Copy constructor deleted
   */
  PassDictionary(const PassDictionary& other) = delete;

  /**
   * @brief Move constructor deleted
   */
  PassDictionary(PassDictionary&& other) = delete;

  /**
   * @brief Copy assignment operator deleted
   */
  PassDictionary& operator=(const PassDictionary& other) = delete;

  /**
   * @brief Move assignment operator deleted
   */
  PassDictionary& operator=(PassDictionary&& other) = delete;

  /**
   * @brief start
   */
  void start();

  /**
   * @brief wait
   */
  void wait();

  /**
   * @brief Destructor
   */
  ~PassDictionary();

private:

  SafeQueue<QByteArray> randomData;
  PassWriter            passWriter;
  RandomReader          randomReader;

};

#endif // PASSDICTIONARY_H
