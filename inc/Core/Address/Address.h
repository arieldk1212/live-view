#ifndef ADDRESS_H
#define ADDRESS_H

#include "Conditions/AddressCondition.h"
#include "Config/DatabaseManager.h"

#include <vector>

/**
 * @brief address api that returns a new instance of this class with the
 * entities (db array) of a specific address,
 */

class Address {
public:
  explicit Address(const std::string &
                       QueryCondition); /* condition of which address to get. */
  ~Address() = default;

  const void GetEntities(const std::string &QueryCondition);
  void ChangeEntities(std::shared_ptr<DatabaseManager> &Manager);

private:
  std::string m_AddressName;
  std::string m_AddressQueryCondition;
  std::vector<std::string> m_AddressEntities;
};

#endif