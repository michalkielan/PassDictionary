#ifndef RANDOMENGINE_H
#define RANDOMENGINE_H

#include <QVector>

/**
 * @brief The RandomEngine interface class
 */
class RandomEngine
{
public:

  /**
   * @brief Constructor
   */
  RandomEngine();

  /**
   * @brief Get vector of char random data
   */
  virtual QVector<uchar> getRandom() = 0;

  /**
   * @brief Destructor
   */
  virtual ~RandomEngine();
};

#endif // RANDOMENGINE_H
