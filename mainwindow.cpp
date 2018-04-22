#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "fileloader.h"
#include "clipboard.h"

#include <QListWidget>
#include <QTextStream>
#include <QClipboard>
#include <QTimer>
#include <QFile>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    clipBoardTimerId(),
    clipboard(nullptr)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::on_loadButton_clicked()
{
  FileLoader fl;
  const auto passFilePath = fl.getPath();

  QFile pass(passFilePath);
  if(pass.open(QIODevice::ReadOnly))
  {
     QTextStream buffer(&pass);
     while(!buffer.atEnd())
     {
        const QString line = buffer.readLine();
        ui->listPassphrases->addItem(line);
     }
     pass.close();
  }
}

void MainWindow::on_clipboardButton_clicked()
{
//  QClipboard* clipboard = QApplication::clipboard();

//  clipboard->setText("123456789");

//  QTimer *timer = new QTimer(this);
//  connect(timer, SIGNAL(timeout()), this, SLOT(clipBoardClearEvent()));
//  timer->start(1000);
//  qDebug() << "Start";
 Clipboard clipboard(1000);

 clipboard.setText("test test");
}

//void MainWindow::clipBoardClearEvent()
//{
//  qDebug() << "End";
//  clipboard->setText("");
//}


