#ifndef PRINTER_H
#define PRINTER_H

#include "passdata.h"

#include <QString>
#include <QObject>

class Printer : public QObject
{
  Q_OBJECT

public:
  Printer(const PassData& passData);
  void print();

  virtual ~Printer() = default;

private:
  PassData passData;

};

#endif // PRINTER_H
