#include "generator/genaratorwindow.h"
#include "ui_genaratorwindow.h"

GenaratorWindow::GenaratorWindow(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::GenaratorWindow)
{
  ui->setupUi(this);
}

GenaratorWindow::~GenaratorWindow()
{
  delete ui;
}
