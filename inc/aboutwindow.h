#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QDialog>

namespace Ui {
class AboutWindow;
}

/**
 * @brief The AboutWindow class
 */
class AboutWindow : public QDialog
{
  Q_OBJECT

public:

  /**
   * @brief Constructor
   * @param parent
   */
  explicit AboutWindow(QWidget* parent = 0);

  /**
    * @brief Destructor
    */
  ~AboutWindow();

private slots:

  /**
   * @brief Ok button clik - end
   */
  void on_okButton_clicked();

private:
  Ui::AboutWindow* ui;
};

#endif // ABOUTWINDOW_H
