#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include <QClipboard>
#include <QTimer>
#include <QObject>

#include "mainwindow.h"
#include "currentpassword.h"

class Clipboard : public QObject
{
  Q_OBJECT

  QClipboard*  clipboard;
  QTimer*      timer;
  unsigned int timeout;
  bool         done;
  MainWindow*  window;

public:
  Clipboard(MainWindow* _mainWindow, const unsigned int _timeout_s);

  void setPass(CurrentPassword& currentPassword);

  virtual ~Clipboard();

private slots:

  void clearClipboardEvent(CurrentPassword& currentPassword);

signals:
  void set_timeout_bar(unsigned int val);
};

#endif // CLIPBOARD_H
