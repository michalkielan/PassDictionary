#ifndef CURRENTPASSWORD_H
#define CURRENTPASSWORD_H

#include <QString>

class CurrentPassword
{
public:
  CurrentPassword();
  void append(const QString pass);
  QString get();
  void clear();

private:
  QString password;
};

#endif // CURRENTPASSWORD_H
