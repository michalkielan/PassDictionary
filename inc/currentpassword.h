#ifndef CURRENTPASSWORD_H
#define CURRENTPASSWORD_H

#include <QString>

/**
 * @brief The CurrentPassword class
 */
class CurrentPassword
{
public:

  /**
   * @brief Constructor
   */
  CurrentPassword();

  /**
   * @brief Copy constructor
   * @param other
   */
  CurrentPassword(const CurrentPassword& other);

  /**
   * @brief Move constructor
   * @param other
   */
  CurrentPassword(CurrentPassword&& other);

  /**
   * @brief Copy assignment operator
   * @param other
   * @return this
   */
  CurrentPassword& operator=(const CurrentPassword& other);

  /**
   * @brief Move assignment operator
   * @param other
   * @return this
   */
  CurrentPassword& operator=(CurrentPassword&& other);

  /**
   * @brief append passphrase to passowrd
   * @param passphrase
   */
  void append(const QString pass);

  /**
   * @brief get password
   * @return  password
   */
  QString get();

  /**
   * @brief set current password to empty string
   */
  void clear();

  /**
    * @brief Destructor
    */
  ~CurrentPassword();

private:
  QString password;
};

#endif // CURRENTPASSWORD_H
