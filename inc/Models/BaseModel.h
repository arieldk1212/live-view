#ifndef BASE_MODEL_H
#define BASE_MODEL_H

#include "Config/DatabaseManager.h"

#include <nlohmann/json.hpp>
#include <pqxx/pqxx>

using Json = nlohmann::json;

/**
 * @brief Abstract base class for database models.
 *
 * Provides an interface for operations on database records, including initialization,
 * insertion, update, and deletion. Derived classes must implement these pure virtual methods
 * to interact with the corresponding database table.
 */
  
/**
 * @brief Pure virtual destructor.
 *
 * Enforces the abstract nature of BaseModel and ensures proper cleanup in derived classes.
 */
  
/**
 * @brief Retrieves the name of the associated database table.
 *
 * Derived classes should implement this method to return the table name relevant to the model.
 *
 * @return A constant reference to a string representing the table name.
 */
  
/**
 * @brief Initializes the model.
 *
 * Performs necessary setup or validation required before the model can be used.
 *
 * @return The result of the initialization operation.
 */
  
/**
 * @brief Inserts a new record into the database.
 *
 * Uses the provided fields to create a new record in the model's table.
 *
 * @param Fields A mapping of field names to their corresponding values.
 * @return The result of the insertion operation.
 */
  
/**
 * @brief Updates existing records in the database.
 *
 * Applies new field values to records that satisfy the specified condition.
 *
 * @param Fields A mapping of field names to their updated values.
 * @param Condition A string representing the condition to identify which records to update.
 * @return The result of the update operation.
 */
  
/**
 * @brief Deletes records from the database.
 *
 * Removes records from the model's table that meet the provided condition.
 *
 * @param Condition A string representing the condition to identify which records to delete.
 * @return The result of the deletion operation.
 */
class BaseModel {
public:
  virtual ~BaseModel() = 0;
  virtual const std::string &GetTableName() const = 0;
  virtual pqxx::result Init() = 0;
  virtual pqxx::result Add(StringUnMap Fields) = 0;
  virtual pqxx::result Update(const StringUnMap &Fields,
                              const std::string &Condition) = 0;
  virtual pqxx::result Delete(const std::string &Condition) = 0;

  // virtual Json SerializeModel(const std::string &Data) = 0;
  // virtual std::string DeserializeModel(const Json &JsonData) = 0;
};

#endif