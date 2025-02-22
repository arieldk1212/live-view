#ifndef LOG_MODEL_H
#define LOG_MODEL_H

#include "BaseModel.h"
#include "Config/DatabaseCommands.h"

#include <chrono>

/**
 * @brief Model class for managing log entries in the database.
 *
 * This class inherits from BaseModel and provides functionalities to initialize the log model
 * and retrieve the name of its associated database table.
 */

/**
 * @brief Constructs a LogModel instance.
 *
 * Initializes the LogModel with a shared pointer to a DatabaseManager to handle database operations.
 */

/**
 * @brief Destroys the LogModel instance.
 *
 * Ensures proper cleanup of resources used by the LogModel.
 */

/**
 * @brief Retrieves the name of the log model's database table.
 *
 * @return A constant reference to the string representing the table name.
 */

/**
 * @brief Initializes the log model.
 *
 * Prepares the model by potentially setting up necessary database structures and initial states.
 *
 * @return The result of the initialization process as a pqxx::result.
 */
class LogModel : public BaseModel {
public:
  explicit LogModel(std::shared_ptr<DatabaseManager> &Manager);
  ~LogModel() override;

  const std::string &GetTableName() const override { return m_TableName; }

  pqxx::result Init() override;
  // pqxx::result Add(const StringUnMap &Fields) override;

private:
  std::shared_ptr<DatabaseManager> m_DatabaseManager;

private:
  std::string m_TableName;
  StringUnMap m_LogFields;
};

#endif