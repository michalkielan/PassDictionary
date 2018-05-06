#ifndef PASSWRITER_H
#define PASSWRITER_H

#include "generator/charactersconfig.h"

#include <QThread>
#include <QFile>

template<typename T>
class SafeQueue;

class QByteArray;

/**
 * @brief The PassWriter thread
 */
class PassWriter : public QThread
{
  Q_OBJECT
  friend class PassDictionary;

private:

  /**
   * @brief Constructor
   * @param words file
   * @param pass file
   * @param queue with random data
   * @param configuration for
   * @param parent
   */
  PassWriter(const QString _words,
             const QString _pass,
             SafeQueue<QByteArray>& _randomData,
             const CharactersConfig _charactersConfig,
             QObject* parent = nullptr);

  /**
   * @brief Copy constructor deleted
   */
  PassWriter(const PassWriter& other) = delete;

  /**
   * @brief Move constructor deleted
   */
  PassWriter(PassWriter&& other) = delete;

  /**
   * @brief Copy assignment operator deleted
   */
  PassWriter& operator=(const PassWriter& other) = delete;

  /**
   * @brief Move assignment operator deleted
   */
  PassWriter& operator=(PassWriter&& other) = delete;

  /**
   * @overload
   */
  void run() override;

  /**
   * @brief Destructor
   */
  virtual ~PassWriter();

signals:

  /**
   * @brief event when all data are wrote into file
   */
  void writeFinished();

private:

  /**
   * @brief write passes into file
   */
  void write();

  QFile                  words;
  QFile                  pass;
  SafeQueue<QByteArray>& randomData;
  CharactersConfig       charactersConfig;
};

#endif // PASSWRITER_H
