#ifndef FILELOADER_H
#define FILELOADER_H

#include <QString>
#include <QMainWindow>

class FileLoader
{
public:
  FileLoader();

  QString getPath() const;

  ~FileLoader() = default;
};

#endif // FILELOADER_H
