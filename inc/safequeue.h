#ifndef SAFEQUEUE_H
#define SAFEQUEUE_H

#include <QMutex>
#include <QWaitCondition>
#include <QQueue>


/**
 * @brief The Queue with mutex and condition variable
 */
template<typename T>
class SafeQueue
{
  QWaitCondition waitCondition;
  QMutex         mutex;
  QQueue<T>      data;

public:

  /**
   * @brief Constructor
   */
  constexpr explicit SafeQueue()
  {
  }

  /**
   * @brief Move constructor
   */
  SafeQueue(SafeQueue&& other) :
    waitCondition{qMove(other.waitCondition)},
    mutex{qMove(other.mutex)},
    data{qMove(other.data)}
  {
  }

  /**
   * @brief Copy constructor deleted
   */
  SafeQueue(const SafeQueue& other) = delete;

  /**
   * @brief Push element into the queue
   * @param [in] item to push
   */
  void push(const T item)
  {
    QMutexLocker lk{&mutex};
    data.push_back(qMove(item));

    lk.unlock();
    waitCondition.notify_all();
  }

  /**
   * @brief Take the top element from the queue
   * @return top element of the queue
   */
  T pop()
  {
    QMutexLocker lk{&mutex};
    while(data.empty())
    {
      waitCondition.wait(lk.mutex());
    }

    const T tmp = data.front();
    data.pop();
    return tmp;
  }

  /**
   * @brief Destructor
   */
  ~SafeQueue() = default;
};

#endif // SAFEQUEUE_H
