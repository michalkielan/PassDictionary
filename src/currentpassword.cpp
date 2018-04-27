#include "currentpassword.h"

CurrentPassword::CurrentPassword()
{
}


CurrentPassword::CurrentPassword(const CurrentPassword& other) :
  password(other.password)
{
}


CurrentPassword::CurrentPassword(CurrentPassword&& other) :
  password(qMove(other.password))
{
}


CurrentPassword& CurrentPassword::operator=(const CurrentPassword& other)
{
  password = other.password;
  return *this;
}


CurrentPassword& CurrentPassword::operator=(CurrentPassword&& other)
{
  password = qMove(other.password);
  return *this;
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

CurrentPassword::~CurrentPassword()
{
}
