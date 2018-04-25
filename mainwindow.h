#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

#include "passdata.h"
#include "currentpassword.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget* parent = 0);
  ~MainWindow();

private slots:
  void on_loadButton_clicked();
  void on_clipboardButton_clicked();
  void on_addButton_clicked();

public slots:
  void set_timeout_bar(unsigned int val);

private:
    Ui::MainWindow* ui;
    PassData        passData;
    CurrentPassword currentPassword;

    void initWidgets();

};

#endif // MAINWINDOW_H
