#ifndef ANURANDOM_H
#define ANURANDOM_H

#include "generator/randomengine.h"

#include <QObject>

class AnuRandom : public QObject, public RandomEngine
{
  Q_OBJECT
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
