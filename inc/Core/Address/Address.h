#ifndef ADDRESS_H
#define ADDRESS_H

#include "Config/DatabaseManager.h"

#include <vector>

/**
 * @brief address api that returns a new instance of this class with the
 * entities (db array) of a specific address, representation of the Address
 * Block.
 */

class Address {
public:
  Address(SharedManager &Manager, std::string IDQuery);
  ~Address() = default;

  [[nodiscard]] const std::map<std::string, std::string> &
  GetAddressValues() const {
    return m_AddressData;
  }

private:
  std::map<std::string, std::string> m_AddressData;
};

#endif