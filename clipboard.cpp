#include "clipboard.h"

#include<QApplication>
#include<QDebug>

Clipboard::Clipboard(const unsigned int _timeout) :
  clipboard(QApplication::clipboard()),
  timer(new QTimer(this)),
  timeout(_timeout),
  done(false)
{
}

void Clipboard::setText(const QString text)
{
  clipboard->setText(text);

  connect(timer, &QTimer::timeout, this, &Clipboard::clearClipboardEvent);
  timer->start(timeout);

  while(!done)
    QCoreApplication::processEvents();
}

void Clipboard::clearClipboardEvent()
{
  qDebug() << "End";
  clipboard->setText("");
  timer->stop();
  done = true;
}

Clipboard::~Clipboard()
{
  qDebug()  << "~Clipboard()";
  delete timer;
}
