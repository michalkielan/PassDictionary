#include "generator/genaratorwindow.h"
#include "ui_genaratorwindow.h"
#include "fileloader.h"

#include <QDir>

GenaratorWindow::GenaratorWindow(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::GenaratorWindow)
{
  ui->setupUi(this);

  const QString homePath = QDir::homePath();
  ui->inputPathLine->setText(homePath);
  ui->outputPathLine->setText(homePath);

}

GenaratorWindow::~GenaratorWindow()
{
  delete ui;
}

void GenaratorWindow::on_inputFileButton_clicked()
{
  const QString path = FileLoader::getPath();
  ui->inputPathLine->setText(path);
}
