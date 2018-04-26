#ifndef PRINTER_H
#define PRINTER_H

#include <QString>
#include <QObject>

class Printer : public QObject
{
  Q_OBJECT

public:
  Printer(const QString passData);
  void print();

  virtual ~Printer() = default;

private:
  QString passData;

};

#endif // PRINTER_H
