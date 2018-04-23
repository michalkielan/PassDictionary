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
  connect(this, &Clipboard::set_timeout_bar, window, &MainWindow::set_timeout_bar);
}

void Clipboard::setPass(CurrentPassword& currentPassword)
{
  if(currentPassword.get().isEmpty())
  {
    return;
  }

  clipboard->setText(currentPassword.get());
  connect(timer, &QTimer::timeout, this, [&,this](){clearClipboardEvent(currentPassword);});

  constexpr const unsigned int maxBarValue {100};
  constexpr const unsigned int timeoutPeriodMs {200};

  set_timeout_bar(maxBarValue);
  timer->start(timeoutPeriodMs);
  timeout *= 4;

  while(!done)
  {
    QCoreApplication::processEvents();
  }
}

void Clipboard::clearClipboardEvent(CurrentPassword& currentPassword)
{
  timeout--;
  static unsigned int barValue {100};
  constexpr const unsigned int tick{2};
  emit set_timeout_bar(barValue);

  if(barValue == 0)
  {
    clipboard->clear();
    timer->stop();

    currentPassword.clear();
    done = true;
  }

  barValue -= tick;
}

Clipboard::~Clipboard()
{
  delete timer;
}
