#ifndef FILELOADER_H
#define FILELOADER_H

#include <QString>

class FileLoader
{
public:
  FileLoader();

  QString getPath() const;

  ~FileLoader() = default;
};

#endif // FILELOADER_H
