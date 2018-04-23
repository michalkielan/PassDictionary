#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "fileloader.h"
#include "clipboard.h"
#include "passphrase.h"

#include <QListWidget>
#include <QTextStream>
#include <QFile>
#include <QRegExp>
#include <QStringList>
#include <QProgressBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

static Passphrase toPassphrase(const QString& passline)
{
  const QRegExp rgx("(\\ |\\t)");
  const QStringList query = passline.split(rgx);

  Passphrase passphrase;
  passphrase.pass = query[0];
  passphrase.word = query[1];

  return passphrase;
}

void MainWindow::on_loadButton_clicked()
{
  const FileLoader fl{this};
  const auto passFilePath = fl.getPath();

  QFile pass(passFilePath);
  if(pass.open(QIODevice::ReadOnly))
  {
     QTextStream buffer(&pass);
     while(!buffer.atEnd())
     {
        const QString line = buffer.readLine();
        const Passphrase passphrase = toPassphrase(line);
        passData.addPass(passphrase);
        ui->listPassphrases->addItem(passphrase.word);
     }
     pass.close();
  }
}

void MainWindow::on_clipboardButton_clicked()
{
  constexpr const unsigned int timeout_s {10};
  Clipboard clipboard(this, timeout_s);
  clipboard.setPass(currentPassword);
}

void MainWindow::on_addButton_clicked()
{
  const QString& word = ui->listPassphrases->currentItem()->text();
  currentPassword.append(passData.getPass(word));
}

void MainWindow::set_timeout_bar(unsigned int val)
{
  ui->timeoutBar->setValue(val);
}
