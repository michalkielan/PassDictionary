#ifndef ANURANDOM_H
#define ANURANDOM_H

#include "generator/randomengine.h"

#include <QObject>

class AnuRandom : public QObject, RandomEngine
{
  Q_OBJECT

public:

  AnuRandom(const qsizetype _len);

  /**
   * @overload
   */
  QVector<uchar> getRandom() override;

  virtual ~AnuRandom();

signals:
  /**
   * @overload
   */
  void readRandom(const QByteArray value);

private:
  qsizetype     len;
  QString       url;
  const QString anuServer {"https://qrng.anu.edu.au"};
};

#endif // ANURANDOM_H
