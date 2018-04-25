#ifndef FILELOADER_H
#define FILELOADER_H

#include "mainwindow.h"

#include <QString>
#include <QMainWindow>

class FileLoader
{
public:
  FileLoader(MainWindow* _window);
  QString getPath() const;
  ~FileLoader() = default;

private:
  MainWindow* window;

};

#endif // FILELOADER_H
