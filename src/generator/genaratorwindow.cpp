#include "generator/genaratorwindow.h"
//#include "generator/anurandom.h"
#include "generator/passdictionary.h"
#include "ui_genaratorwindow.h"
#include "fileloader.h"
#include "generator/charactersconfig.h"

#include <QDir>
#include <QThread>
#include <QTimer>
#include <QtGlobal>

GenaratorWindow::GenaratorWindow(QWidget* parent) :
  QDialog(parent),
  ui(new Ui::GenaratorWindow),
  wordsPath(),
  passphrasesPath()
{
  ui->setupUi(this);
  initWidgets();
}

void GenaratorWindow::initWidgets()
{
 setDefaultCheckBoxes();
 setDefaultEditLines();
}

void GenaratorWindow::setDefaultEditLines()
{
  const QString homePath = QDir::homePath();
  ui->inputPathLine->setText(homePath);
  ui->outputPathLine->setText(homePath);
}

void GenaratorWindow::setDefaultCheckBoxes()
{
  ui->upperLettersCheckBox->setChecked(true);
  ui->lowerLettersCheckBox->setChecked(true);
  ui->numbersCheckBox->setChecked(true);
  ui->ambigousCheckBox->setChecked(false);
}

GenaratorWindow::~GenaratorWindow()
{
  delete ui;
}

void GenaratorWindow::on_generateButton_clicked()
{
  ui->generateButton->setEnabled(false);
  CharactersConfig charactersConfig;
  charactersConfig.upperWords = ui->upperLettersCheckBox->isChecked();
  charactersConfig.lowerWords = ui->lowerLettersCheckBox->isChecked();
  charactersConfig.numbers = ui->numbersCheckBox->isChecked();
  charactersConfig.ambigous = ui->ambigousCheckBox->isChecked();
  charactersConfig.passphraseLength = 5;

  const QString passPath = QDir::tempPath() + "/pass_tmp.txt";
  PassDictionary passDictionary{wordsPath, passPath, charactersConfig};

  passDictionary.start();
  passDictionary.wait();
  ui->generateButton->setEnabled(true);
}

void GenaratorWindow::on_inputFileButton_clicked()
{
  wordsPath = FileLoader::getPath();
  ui->inputPathLine->setText(wordsPath);
}
