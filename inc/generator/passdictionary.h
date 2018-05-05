#ifndef PASSDICTIONARY_H
#define PASSDICTIONARY_H

#include "safequeue.h"
#include "generator/passwriter.h"
#include "generator/randomread.h"

#include <QFile>
#include <QObject>
#include <QAtomicInt>
#include <QSharedPointer>

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

  void start();
  void wait();

private:

  SafeQueue<QByteArray> randomData;
  QAtomicInt            done;
  PassWriter            passWriter;
  RandomReader          randomReader;

};

#endif // PASSDICTIONARY_H
