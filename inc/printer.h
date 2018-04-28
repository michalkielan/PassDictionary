#ifndef PRINTER_H
#define PRINTER_H

#include "passdata.h"

#include <QObject>

/**
 * @brief The Printer QObject class
 */
class Printer : public QObject
{
  Q_OBJECT

public:

  /**
   * @brief Constructor
   */
  Printer(const PassData& _passData);

  /**
   * @brief Copy constructor deleted
   */
  Printer(const Printer& other) = delete;

  /**
   * @brief Move constructor deleted
   */
  Printer(Printer&& other) = delete;

  /**
   * @brief Copy assignment operator deleted
   */
  Printer& operator=(const Printer& other) = delete;

  /**
   * @brief Move assignment operator deleted
   */
  Printer& operator=(Printer&& other) = delete;

  /**
   * @brief Open print dialog window to print setup
   */
  void print() const;

  /**
   * @brief Destructor
   */
  ~Printer();

private:
  PassData passData;

};

#endif // PRINTER_H
