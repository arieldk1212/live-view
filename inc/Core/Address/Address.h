#ifndef ADDRESS_H
#define ADDRESS_H

#include "Conditions/AddressCondition.h"
#include "Config/DatabaseManager.h"

#include <vector>

// Entity
// TODO: add logic for the data separation from the full address to entity
// block. INFO: when i get the address from the Address Class, it will be passed
// down to Entity and the logic of the address separation to entities will be
// dealt here, meaning i probably want to change the Entity Ctor to the address
// itself, and the separate to Entities ( Data Structures ).
// INFO: the address class will inherit from entity due to the need use of the
// private entity members and their functionality.

/**
 * @brief address api that returns a new instance of this class with the
 * entities (db array) of a specific address,
 */

class Address {
public:
  explicit Address(const std::string &
                       QueryCondition); /* condition of which address to get. */
  ~Address() = default;

  std::vector<std::string> &
  GetEntities(const std::string &QueryCondition) const;
  void ChangeEntities(std::shared_ptr<DatabaseManager> &Manager);

private:
  std::string m_AddressName;
  std::string m_AddressQueryCondition;
  std::vector<std::string> m_AddressEntities;
};

#endif