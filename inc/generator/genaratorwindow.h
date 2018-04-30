#ifndef GENARATORWINDOW_H
#define GENARATORWINDOW_H

#include <QDialog>
#include <QString>

namespace Ui {
class GenaratorWindow;
}

class GenaratorWindow : public QDialog
{
  Q_OBJECT

public:
  explicit GenaratorWindow(QWidget* parent = 0);
  ~GenaratorWindow();

private slots:

  /**
   * @brief Input file (...) button cliked
   */
  void on_inputFileButton_clicked();

  /**
   * @brief Generate button clicked event
   */
  void on_generateButton_clicked();

private:
  Ui::GenaratorWindow* ui;
  QString wordsPath;
  QString passphrasesPath;

  /**
   * @brief Init widgets
   */
  void initWidgets();

  /**
   * @brief Set default values in checkboxes
   */
  void setDefaultCheckBoxes();

  /**
   * @brief Set default input line editors
   */
  void setDefaultEditLines();
};

#endif // GENARATORWINDOW_H
