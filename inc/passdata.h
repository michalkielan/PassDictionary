#ifndef PASSDATA_H
#define PASSDATA_H

#include "passphrase.h"

#include <QMap>

/**
 * @brief The PassData class
 */
class PassData
{
public:

  /**
   * @brief Constructor
   */
  PassData();

  /**
   * @brief Copy constructor
   */
  PassData(const PassData& other);

  /**
   * @brief Move constructor
   */
  PassData(PassData&& other);

  /**
   * @brief Copy assignment operator
   */
  PassData& operator=(const PassData& other);

  /**
   * @brief Move assignment operator
   */
  PassData& operator=(PassData&& other);

  /**
   * @brief Add passphrase
   * @param passphrase
   */
  void addPass(const Passphrase passphrase);

  /**
   * @brief Get pass assigned to word
   * @param word
   * @return pass
   */
  QString getPass(const QString word) const;

  /**
   * @brief Get html string to make pdf from
   * @return html code string with list of passphrases
   */
  QString getPdfHtml() const;

  /**
   * @brief Clear map with pass and words
   */
  void clear();

  /**
    * @brief Destructor
    */
  ~PassData();

private:
  QMap<QString, QString> passphrases;

};

#endif // PASSDATA_H
