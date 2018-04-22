#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

#include <memory>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

  void on_loadButton_clicked();
  void on_clipboardButton_clicked();
//  void clipBoardClearEvent();

private:
    Ui::MainWindow* ui;
    int clipBoardTimerId;
    QClipboard* clipboard;

protected:


};

#endif // MAINWINDOW_H
