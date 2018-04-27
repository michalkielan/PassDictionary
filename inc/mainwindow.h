#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "passdata.h"
#include "currentpassword.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
  Q_OBJECT

public:

  /**
   * @brief Constructor
   * @param parent
   */
  explicit MainWindow(QWidget* parent = 0);

  /**
    * Destructor
    */
  ~MainWindow();

private slots:

  /**
   * @brief Clipboard button clicked event
   */
  void on_clipboardButton_clicked();

  /**
   * @brief Add button clicked event
   */
  void on_addButton_clicked();

  /**
   * @brief Menu->About clicked event
   */
  void on_actionAbout_triggered();

  /**
   * @brief Menu->Open Pass File clicked event
   */
  void on_action_Open_pass_file_triggered();

  /**
   * @brief Search line event call when text is changed
   * @param arg1
   */
  void on_searchLineEdit_textChanged(const QString &arg1);

  /**
   * @brief Close file event
   */
  void on_actionClose_file_triggered();

  /**
   * @brief on_action_Exit_triggered
   */
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
