#include "fileloader.h"

#include <QFileDialog>
#include <QDir>
#include <QMainWindow>

QString FileLoader::getPath()
{
  const QString openPath = QDir::homePath();
  const auto passFilePath = QFileDialog::getOpenFileName(nullptr,
    QMainWindow::tr("Open passphrase file"), openPath, QMainWindow::tr("Passphrase Files (*.txt *.pass)"));

  return passFilePath;
}
