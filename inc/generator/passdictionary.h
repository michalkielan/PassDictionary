#ifndef PASSDICTIONARY_H
#define PASSDICTIONARY_H

#include "safequeue.h"

#include <QFile>
#include <QObject>
#include <QAtomicInt>

/**
 * @brief The PassDictionary class
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
  PassDictionary(const QString _words, QString _pass);

public slots:

  /**
   * @brief write random data from randomData queue to file
   * @param randomData
   */
  void write();

  /**
   * @brief save random data to randomData queue
   * @param randomData
   */
  void readRandom();

signals:
  void writeFinished();
  void readRandomFinished();

private:

  QFile                 words;
  QFile                 pass;
  SafeQueue<QByteArray> randomData;
  QAtomicInt            done;
};

#endif // PASSDICTIONARY_H
