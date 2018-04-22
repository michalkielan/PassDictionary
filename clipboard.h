#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include <QClipboard>
#include <QTimer>
#include <QObject>

class Clipboard : public QObject
{
  Q_OBJECT

  QClipboard* clipboard;
  QTimer* timer;
  unsigned int timeout;
  bool done;

public:
  Clipboard(const unsigned int _timeout);

  void setText(const QString text);

  virtual ~Clipboard();

private slots:

  void clearClipboardEvent();
};

#endif // CLIPBOARD_H
