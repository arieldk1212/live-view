#ifndef ADDRESS_H
#define ADDRESS_H

#include "Conditions/AddressCondition.h"
#include "Config/DatabaseManager.h"

#include <vector>

/**
 * @brief Represents an address and facilitates retrieval and modification of its associated entities.
 *
 * This class encapsulates the state of an address, including its name, query condition, and related entities.
 * It provides functionality to initialize an address instance with a specific query condition for fetching entities,
 * retrieve those entities, and update them using a database manager.
 */

/**
 * @brief Constructs an Address instance.
 *
 * Initializes the Address object using the provided query condition, which determines the set of address entities to retrieve.
 *
 * @param QueryCondition The condition used to query and filter address entities.
 */

/**
 * @brief Retrieves address entities based on a query condition.
 *
 * Fetches the entities associated with the address by applying the provided query condition.
 *
 * @param QueryCondition The condition used to filter and retrieve address entities.
 */

/**
 * @brief Updates the address entities.
 *
 * Applies modifications to the stored address entities using the provided database manager.
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