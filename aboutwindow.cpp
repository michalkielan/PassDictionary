#include "aboutwindow.h"
#include "ui_aboutwindow.h"

#include <QLabel>

AboutWindow::AboutWindow(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::AboutWindow)
{
  ui->setupUi(this);

  ui->copyrightLabel->setText("Copyright (c) 2018 Michał Kielan");

  ui->licenceLabel->setWordWrap(true);
  ui->licenceLabel->setText("The program is distributed under the terms of "
                            "the GNU General Public License version 2");
}

AboutWindow::~AboutWindow()
{
  delete ui;
}

void AboutWindow::on_pushButton_clicked()
{
  this->close();
}
