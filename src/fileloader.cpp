#include "fileloader.h"

#include <QFileDialog>
#include <QDir>
#include <QObject>
#include <QMainWindow>

FileLoader::FileLoader(MainWindow* _window) :
  window(_window)
{
}

QString FileLoader::getPath() const
{
  const QString openPath = QDir::homePath();
  const auto passFilePath = QFileDialog::getOpenFileName(window,
   window->tr("Open passphrase file"), openPath, window->tr("Passphrase Files (*.txt *.pass)"));

  return passFilePath;
}
