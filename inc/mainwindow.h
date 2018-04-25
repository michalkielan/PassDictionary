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
  void on_clipboardButton_clicked();
  void on_addButton_clicked();
  void on_actionAbout_triggered();
  void on_action_Open_pass_file_triggered();
  void on_searchLineEdit_textChanged(const QString &arg1);
  void on_actionClose_file_triggered();

  void on_action_Exit_triggered();

  void on_action_Print_triggered();

public slots:
  void set_timeout_bar(unsigned int val);

private:
    Ui::MainWindow* ui;
    PassData        passData;
    CurrentPassword currentPassword;

    void initWidgets();
    void enableWidgets(const bool status);

};

#endif // MAINWINDOW_H
