#include "clipboard.h"
#include "mainwindow.h"

#include<QApplication>
#include<QClipboard>
#include<QDebug>
#include<QTimer>


Clipboard::Clipboard(MainWindow *_mainWindow, const unsigned int _timeout_s) :
  clipboard(QApplication::clipboard()),
  timer(new QTimer(this)),
  timeout(_timeout_s),
  done(false),
  window(_mainWindow)
{
  connect(this, &Clipboard::set_timeout_bar, window, &MainWindow::set_timeout_bar);
}

void Clipboard::copyToClipboard(CurrentPassword& currentPassword)
{
  if(currentPassword.get().isEmpty())
  {
    return;
  }

  clipboard->setText(currentPassword.get());
  connect(timer.data(), &QTimer::timeout, this, [&,this](){timeoutEvent(currentPassword);});

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

void Clipboard::timeoutEvent(CurrentPassword& currentPassword)
{
  timeout--;
  constexpr const unsigned int maxBarValue {100};
  static unsigned int barValue {maxBarValue};
  constexpr const unsigned int tick{2};
  emit set_timeout_bar(barValue);

  if(barValue == 0)
  {
    clipboard->clear();
    timer->stop();

    currentPassword.clear();
    barValue = maxBarValue;
    done = true;
  }

  barValue -= tick;
}

Clipboard::~Clipboard()
{
}
