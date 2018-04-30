#include "generator/genaratorwindow.h"
#include "generator/anurandom.h"
#include "ui_genaratorwindow.h"
#include "fileloader.h"

#include <QDir>

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

  AnuRandom ar{charactersTypes.passphraseLength};
  ar.getRandom();
}

void GenaratorWindow::on_inputFileButton_clicked()
{
  wordsPath = FileLoader::getPath();
  ui->inputPathLine->setText(wordsPath);
}
