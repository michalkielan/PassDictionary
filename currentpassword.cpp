#include "currentpassword.h"

CurrentPassword::CurrentPassword()
{
}

void CurrentPassword::append(const QString pass)
{
  password.append(pass);
}

QString CurrentPassword::get()
{
  return password;
}

void CurrentPassword::clear()
{
  password.clear();
}
