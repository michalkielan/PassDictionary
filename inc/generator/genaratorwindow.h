#ifndef GENARATORWINDOW_H
#define GENARATORWINDOW_H

#include <QDialog>

namespace Ui {
class GenaratorWindow;
}

class GenaratorWindow : public QDialog
{
  Q_OBJECT

public:
  explicit GenaratorWindow(QWidget *parent = 0);
  ~GenaratorWindow();

private slots:
  void on_inputFileButton_clicked();

private:
  Ui::GenaratorWindow *ui;
};

#endif // GENARATORWINDOW_H
