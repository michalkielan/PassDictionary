#ifndef ANURANDOM_H
#define ANURANDOM_H

#include "generator/randomengine.h"

class AnuRandom : public RandomEngine
{
public:

  AnuRandom(const qsizetype _len);

  /**
   * @overload
   */
  QVector<uchar> getRandom() override;

  virtual ~AnuRandom();

private:
  qsizetype     len;
  QString       url;
  const QString anuServer {"https://qrng.anu.edu.au"};

};

#endif // ANURANDOM_H
