#include "clipboard.h"

#include "mainwindow.h"

#include<QApplication>
#include<QDebug>

Clipboard::Clipboard(MainWindow *_mainWindow, const unsigned int _timeout_s) :
  clipboard(QApplication::clipboard()),
  timer(new QTimer(this)),
  timeout(_timeout_s),
  done(false),
  window(_mainWindow)
{
  connect(this, &Clipboard::bar_decrement, window, &MainWindow::bar_decrement);
}

void Clipboard::setPass(CurrentPassword& currentPassword)
{
  if(currentPassword.get().isEmpty())
  {
    return;
  }

  clipboard->setText(currentPassword.get());
  connect(timer, &QTimer::timeout, this, [&,this](){clearClipboardEvent(currentPassword);});

 timer->start(1000);

  while(!done)
  {
    QCoreApplication::processEvents();
  }
}

void Clipboard::clearClipboardEvent(CurrentPassword& currentPassword)
{
  timeout--;
  emit bar_decrement();

  if(timeout == 0)
  {
    clipboard->clear();
    timer->stop();

    currentPassword.clear();
    done = true;
  }
}

Clipboard::~Clipboard()
{
  delete timer;
}
