#ifndef RANDOMREAD_H
#define RANDOMREAD_H

#include <QThread>

template<typename T>
class SafeQueue;

class QByteArray;

/**
 * @brief The RandomReader thread class
 */
class RandomReader : public QThread
{
  Q_OBJECT
  friend class PassDictionary;

private:

  /**
   * @brief Constructor
   * @param queue with random data
   * @param parent
   */
  RandomReader(SafeQueue<QByteArray>& _randomData, QObject* parent = nullptr);

  /**
   * @overload
   */
  void run() override;

  /**
   * @brief read random data
   */
  void readRand();

private:
  SafeQueue<QByteArray>& randomData;
};

#endif // RANDOMREAD_H
