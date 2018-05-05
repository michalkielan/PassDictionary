#ifndef PASSDICTIONARY_H
#define PASSDICTIONARY_H

#include "safequeue.h"

#include <QFile>

/**
 * @brief The PassDictionary class
 */
class PassDictionary
{

public:

  /**
   * @brief PassDictionary
   * @param file with words
   * @param file with passphrases
   */
  PassDictionary(const QString _words, QString _pass);

  /**
   * @brief write random data from randomData queue to file
   * @param randomData
   */
  void write(SafeQueue<QByteArray>& randomData);

  /**
   * @brief save random data to randomData queue
   * @param randomData
   */
  void readRandom(SafeQueue<QByteArray>& randomData);

private:

  QString getString(QByteArray randomData) const;

  QFile words;
  QFile pass;
};

#endif // PASSDICTIONARY_H
