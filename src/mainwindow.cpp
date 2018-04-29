#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "fileloader.h"
#include "clipboard.h"
#include "passphrase.h"
#include "aboutwindow.h"
#include "printer.h"

#include <QListWidget>
#include <QTextStream>
#include <QFile>
#include <QRegExp>
#include <QStringList>
#include <QProgressBar>
#include <QDebug>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  initWidgets();
}

void MainWindow::initWidgets()
{
  enableWidgets(false);
  ui->clipboardButton->setEnabled(false);
}

void MainWindow::enableWidgets(const bool status)
{
  ui->addButton->setEnabled(status);
  ui->timeoutBar->setEnabled(status);
  ui->listPassphrases->setEnabled(status);
  ui->searchLineEdit->setEnabled(status);
}

MainWindow::~MainWindow()
{
  delete ui;
}

static Passphrase toPassphrase(const QString& passline)
{
  const QRegExp rgx("(\\ |\\t)");
  const QStringList query = passline.split(rgx);

  if(query.size() != 2)
  {
    throw "Bad pass file format";
  }

  Passphrase passphrase;
  passphrase.pass = query[0];
  passphrase.word = query[1];

  return passphrase;
}

void MainWindow::on_clipboardButton_clicked()
{
  ui->clipboardButton->setEnabled(false);
  constexpr const unsigned int timeout_s {10};

  Clipboard clipboard(this, timeout_s);
  clipboard.copyToClipboard(currentPassword);
}

void MainWindow::on_addButton_clicked()
{
  const QString& word = ui->listPassphrases->currentItem()->text();
  currentPassword.append(passData.getPass(word));
  ui->clipboardButton->setEnabled(true);
}

void MainWindow::set_timeout_bar(unsigned int val)
{
  ui->timeoutBar->setValue(val);
}

void MainWindow::on_actionAbout_triggered()
{
  AboutWindow about;
  about.setModal(true);
  about.exec();
}

void MainWindow::on_action_Open_pass_file_triggered()
{
  ui->listPassphrases->clear();

  const auto passFilePath = FileLoader::getPath();

  QFile pass(passFilePath);
  if(pass.open(QIODevice::ReadOnly))
  {
    enableWidgets(true);

    QTextStream buffer(&pass);
    while(!buffer.atEnd())
    {
      try
      {
        const QString line = buffer.readLine();
        const Passphrase passphrase = toPassphrase(line);
        passData.addPass(passphrase);
        ui->listPassphrases->addItem(passphrase.word);
      }
      catch(...)
      {
        qDebug() << "Parse line failed";
      }
    }
    pass.close();
  }
}

void MainWindow::on_searchLineEdit_textChanged(const QString &arg1)
{
  const QString& textToSearch = arg1;
  const auto elements = ui->listPassphrases->count();
  bool oldBool = false;

  for(int i = 0; i < elements; ++i)
  {
    if(ui->listPassphrases->item(i)->text().startsWith(textToSearch))
    {
       ui->listPassphrases->item(i)->setHidden(false);
       oldBool = true;
    }
    else
    {
      ui->listPassphrases->item(i)->setHidden(true);

      if (oldBool == true) {
        // falling edge detected, so let's 
        // setHidden from elem i+1 to the last.
        return on_searchLineEdit_setHiddenFromElem(i+1);
      }    
    }
  }
}

void MainWindow::on_searchLineEdit_setHiddenFromElem(int i)
{
  const auto elements = ui->listPassphrases->count();
  for(; i < elements; ++i) {
      ui->listPassphrases->item(i)->setHidden(true);
  }
  return;
}

void MainWindow::on_actionClose_file_triggered()
{
  ui->listPassphrases->clear();
  passData.clear();
  currentPassword.clear();
  enableWidgets(false);
}

void MainWindow::on_action_Exit_triggered()
{
  this->close();
}

void MainWindow::on_action_Print_triggered()
{
  Printer printer(passData);
  printer.print();
}
