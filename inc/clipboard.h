#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include "mainwindow.h"
#include "currentpassword.h"

#include <QClipboard>
#include <QObject>
#include <QScopedPointer>
#include <QTimer>

/**
 * @brief The Clipboard class
 */
class Clipboard : public QObject
{
  Q_OBJECT

public:
  /**
   * @brief Constructor
   * @param _mainWindow mainwindow object
   * @param _timeout_s  timeout[s] for clear clipboard
   */
  Clipboard(MainWindow* _mainWindow, const unsigned int _timeout_s);

  /**
   * @brief Copy constructor deleted
   */
  Clipboard(const Clipboard& other) = delete;
  /**
   * @brief Move constructor deleted
   */
  Clipboard(Clipboard&& other) = delete;

  /**
   * @brief Copy assignment operator deleted
   */
  Clipboard& operator=(const Clipboard& other) = delete;

  /**
   * @brief Move assignment operator deleted
   */
  Clipboard& operator=(Clipboard&& other) = delete;

  /**
   * @brief Copy pass to clipboard
   * @param currentPassword reference
   */
  void copyToClipboard(CurrentPassword& currentPassword);

  /**
   * @brief Destructor
   */
  ~Clipboard();

private slots:

  /**
   * @brief Event for timeout (called in every tick)
   * @param currentPassword
   */
  void timeoutEvent(CurrentPassword& currentPassword);

signals:

  /**
   * @brief set value in timeout bar
   * @param value
   */
  void set_timeout_bar(unsigned int val);

private:
  QClipboard*            clipboard;
  QScopedPointer<QTimer> timer;
  unsigned int           timeout;
  bool                   done;
  MainWindow*            window;
};

#endif // CLIPBOARD_H
