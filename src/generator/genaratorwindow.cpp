#include "generator/genaratorwindow.h"
//#include "generator/anurandom.h"
#include "generator/passdictionary.h"
#include "ui_genaratorwindow.h"
#include "fileloader.h"

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

struct CharactersTypes
{
  bool upperWords;
  bool lowerWords;
  bool numbers;
  bool symbols;
  bool ambigous;
  int passphraseLength;
};

void GenaratorWindow::on_generateButton_clicked()
{
  CharactersTypes charactersTypes;
  charactersTypes.upperWords = ui->upperLettersCheckBox->isChecked();
  charactersTypes.lowerWords = ui->lowerLettersCheckBox->isChecked();
  charactersTypes.numbers = ui->numbersCheckBox->isChecked();
  charactersTypes.ambigous = ui->ambigousCheckBox->isChecked();
  charactersTypes.passphraseLength = 5;

  QString passPath = QDir::tempPath() + "pass_tmp.txt";
  PassDictionary passDictionary{wordsPath, passPath};

//  void write(SafeQueue<QByteArray>& randomData);
//  void readRandom(SafeQueue<QByteArray>& randomData);

//  QThread writer;
//  passDictionary.moveToThread(&writer);

//  connect(&writer, &QThread::started, &passDictionary, &PassDictionary::write);
//  connect(&passDictionary, &PassDictionary::writeFinished, &writer, &QThread::quit);

//  connect(&passDictionary, &PassDictionary::writeFinished, passDictionary, &PassDictionary::deleteLater);

//  connect(&writer, &QThread::finished, &writer, &QThread::deleteLater);

//  writer.start();

}

void GenaratorWindow::on_inputFileButton_clicked()
{
  wordsPath = FileLoader::getPath();
  ui->inputPathLine->setText(wordsPath);
}
