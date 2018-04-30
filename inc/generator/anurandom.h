#ifndef ANURANDOM_H
#define ANURANDOM_H

#include "generator/randomengine.h"

class AnuRandom : public RandomEngine
{
public:

  AnuRandom();

  /**
   * @overload
   */
  QVector<uchar> getRandom() override;

  virtual ~AnuRandom();

private:
  qsizetype len;
  QString   url;

};

#endif // ANURANDOM_H
