#include "fileloader.h"

#include <QFileDialog>
#include <QDir>

FileLoader::FileLoader()
{

}

QString FileLoader::getPath() const
{
//  const QString openPath = QDir::homePath();
//  const auto passFilePath = QFileDialog::getOpenFileName(this,
//      tr("Open passphrase file"), openPath, tr("Passphrase Files (*.txt *.pass)"));

  return "";//passFilePath;
}
