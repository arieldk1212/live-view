#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include "../Core/UUID.h"
#include "Database.h"
#include "DatabaseCommands.h"
#include "Logger.h"

#include <iostream>
#include <memory>
#include <type_traits>
#include <utility>

/**
 * @class DatabaseManager
 * @brief Manges the database models and operations, in front of the db itself.
 */
class DatabaseManager {
public:
public:
  /**
   * @brief Constructs the DatabaseManager object, according to the database's
   * connection string.
   */
  DatabaseManager(const std::string &DatabaseConnectionString);
  /**
   * @brief Deconstructs the DatabaseManager object, clearing the database
   * models.
   */
  ~DatabaseManager();

  DatabaseManager(const DatabaseManager &other) = delete;
  DatabaseManager &operator=(const DatabaseManager &other) = delete;

  DatabaseManager(DatabaseManager &&other) noexcept = delete;
  DatabaseManager &operator=(DatabaseManager &&other) noexcept = delete;

  /**
   * @brief check the status of the database connection.
   * @return bool
   */
  bool IsDatabaseConnected() const;

  /**
   * @brief  serializes the fields of the model, query preparation.
   * @param ModelFields
   * @return std::string
   */
  std::string QuerySerialization(const StringUnMap &ModelFields);

  /**
   * @brief creates a new DatabaseModel object, creates a new table in the
   * database with the given parameters.
   * @param ModelName string, Model/Table name.
   * @param ModelFields StringMap, fields of the Model/Table.
   * @return pqxx::result
   */
  pqxx::result AddModel(const std::string &ModelName,
                        const StringUnMap &ModelFields);
  /**
   * @brief removes the table from the database and the object of the
   * DatabaseModel class.
   * @param ModelName
   * @return pqxx::result
   */
  pqxx::result RemoveModel(const std::string &ModelName);
  /**
   * @brief clear all the data in a given table.
   * @param ModelName
   * @return pqxx::result
   */
  pqxx::result TruncateModel(const std::string &ModelName);
  /**
   * @brief Get the Model Data object from the database.
   * @param ModelName
   * @return pqxx::result
   */
  pqxx::result GetModelData(const std::string &ModelName);
  /**
   * @brief Get the specifig Model Data object from the database.
   * @param ModelName
   * @param FieldName
   * @param FieldValue
   * @return pqxx::result
   */
  pqxx::result GetModelData(const std::string &ModelName,
                            const std::string &FieldName,
                            const std::string &FieldValue);
  /**
   * @brief add fields to an existing table.
   * @param ModelName string, name of the model/table.
   * @param FieldName string, the field name.
   * @param FieldType string, the field type.
   */
  pqxx::result AddColumn(const std::string &ModelName,
                         const std::string &FieldName,
                         const std::string &FieldType);
  /**
   * @brief remove field from an existing table.
   * @param ModelName
   * @param FieldName
   * @return pqxx::result
   */
  pqxx::result DropColumn(const std::string &ModelName,
                          const std::string &FieldName);
  /**
   * @brief alter the type of a specific field in the table.
   * @param ModelName
   * @param FieldName
   * @param NewFieldType
   * @return pqxx::result
   */
  pqxx::result AlterColumn(const std::string &ModelName,
                           const std::string &FieldName,
                           const std::string &NewFieldType);
  /**
   * @brief inserts data to the table's database.
   * @param ModelName
   * @param Fields
   * @return pqxx::result
   */
  pqxx::result InsertInto(const std::string &ModelName,
                          const StringUnMap &Fields);
  /**
   * @brief updates the table's field value with a specific condition.
   * @param ModelName
   * @param FieldName
   * @param NewFieldValue
   * @param Condition
   * @return pqxx::result
   */
  pqxx::result UpdateColumn(const std::string &ModelName,
                            const std::string &FieldName,
                            const std::string &NewFieldValue,
                            const std::string &Condition);
  /**
   * @brief updates the table's multiple fields values with a specific
   * condition.
   * @param ModelName
   * @param Fields
   * @param Condition
   * @return pqxx::result
   */
  pqxx::result UpdateColumns(const std::string &ModelName,
                             const StringUnMap &Fields,
                             const std::string &Condition);
  /**
   * @brief delete a record from the table.
   * @param ModelName
   * @param Condition
   */
  pqxx::result DeleteRecord(const std::string &ModelName,
                            const std::string &Condition);

private:
  /**
   * @brief private database CRD related methods, they connect only with the
   * model editor above and in DatabaseModel.
   */
  pqxx::result MCrQuery(const std::string &TableName, const std::string &Query);
  pqxx::result CreateTable(const std::string &TableName,
                           const StringUnMap &TableFields);
  pqxx::result GetTableData(const std::string &TableName);
  pqxx::result GetTableData(const std::string &TableName,
                            const std::string &TableFieldName,
                            const std::string &TableFieldValue);
  pqxx::result DeleteTable(const std::string &TableName,
                           DatabaseQueryCommands QueryCommand);
  // pqxx::result MUQuery(const std::string &TableName, const std::string
  // &Query);

private:
  bool m_IsConnected;
  std::string m_DatabaseConnectionString;
  std::unique_ptr<DatabaseConnection> m_DatabaseManager;

private:
  /** @brief to create the connection pool we need, create a new connection,
   * add, remove, lock. */
  // std::shared_ptr<DatabasePoolManager> m_DatabaseManager;
};

/**
 * @class DatabaseConnectionPoolManager
 * @brief this class is reponsible for the database connection pool, currently
 * still in development.
 * @todo implement this class, adjust connections accordingly, study about
 * pool's more.
 */

// class DBManager {
// public:
//   DBManager(std::string &&ConnectionString) noexcept;
//   ~DBManager() = default;

//   void AddConnection(std::unique_ptr<DatabaseConnection> Connection);
//   void RemoveConnection(std::unique_ptr<DatabaseConnection> Connection);
//   std::unique_ptr<DatabaseConnection> LockConnection();

// private:
//   size_t m_DatabaseConntectionPoolSize;
//   std::mutex m_DatabaseConnectionPoolMutex;
//   std::string m_DatabaseConnectionString;
//   std::vector<std::unique_ptr<DatabaseManager>> m_DatabaseConnectionPool;
// };

#endif