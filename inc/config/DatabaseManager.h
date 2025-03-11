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
  /**
   * @brief Constructs the DatabaseManager object, according to the database's
   * connection string.
   */
  explicit DatabaseManager(const std::string &DatabaseConnectionString);
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
  [[nodiscard]] inline bool IsDatabaseConnected() const {
    return m_DatabaseManager->IsDatabaseConnected();
  }
  /**
   * @brief Get the Connection String object
   * @return std::string
   */
  [[nodiscard]] inline std::string GetConnectionString() const {
    return m_DatabaseManager->GetConnectionString();
  }

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
   * @brief Get the specific Model Data object from the database.
   * @param ModelName
   * @param FieldName
   * @param template <T>arg
   * @return pqxx::result
   */
  template <typename T>
  pqxx::result GetModelData(const std::string &ModelName,
                            const std::string &FieldName, T &&arg) {
    return GetTableData(ModelName, FieldName, std::forward<T>(arg));
  }
  /**
   * @brief Get the specific Model Data object from the database.
   * @tparam Args
   * @param ModelName
   * @param FirstFieldName
   * @param SecondFieldName
   * @param arg
   * @return pqxx::result
   */
  template <typename... Args>
  pqxx::result GetModelDataArgs(const std::string &ModelName,
                                const std::string &FirstFieldName,
                                const std::string &SecondFieldName,
                                Args &&...arg) {
    return GetTableData(ModelName, FirstFieldName, SecondFieldName,
                        std::forward<Args>(arg)...);
  }
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
   * @param Condition
   * @param Params
   * @return pqxx::result
   */
  pqxx::result UpdateColumn(const std::string &ModelName,
                            std::string_view FieldName,
                            std::string_view Condition,
                            const pqxx::params &Params);
  /**
   * @brief updates the table's multiple fields values with a specific
   * condition.
   * @param ModelName
   * @param Fields
   * @param Condition
   * @param Params
   * @return pqxx::result
   */
  pqxx::result UpdateColumns(const std::string &ModelName,
                             const StringUnMap &Fields,
                             std::string_view Condition,
                             const pqxx::params &Params);
  /**
   * @brief delete a record from the table.
   * @param ModelName
   * @param Condition
   * @param Params
   */
  pqxx::result DeleteRecord(const std::string &ModelName,
                            std::string_view Condition,
                            const pqxx::params &Params);

private:
  /**
   * @brief private database CRD related methods, they connect only with the
   * model editor above and in DatabaseModel.
   */
  pqxx::result MCrQuery(const std::string &TableName, const std::string &Query);
  /**
   * @brief overload for the function, improving security issues when needed
   * user input.
   */
  template <typename... Args>
  pqxx::result MCrQuery(const std::string &TableName, const std::string &Query,
                        Args &&...args) {
    try {
      pqxx::result Response =
          m_DatabaseManager->CrQuery(Query, std::forward<Args>(args)...);
      return Response;
    } catch (pqxx::sql_error const &e) {
      APP_ERROR("MCRQUERY(PF) ERROR AT TABLE - " + TableName + " " +
                std::string(e.what()));
      return {};
    } catch (std::exception const &e) {
      APP_ERROR("MCRQUERY(PF) GENERAL ERROR - " + std::string(e.what()));
      return {};
    }
  }
  pqxx::result MWQuery(const std::string &TableName, const std::string &Query);
  pqxx::result CreateTable(const std::string &TableName,
                           const StringUnMap &TableFields);
  pqxx::result GetTableData(const std::string &TableName);
  template <typename T>
  pqxx::result GetTableData(const std::string &TableName,
                            const std::string &TableFieldName, T &&arg) {
    std::string query;
    query.append(DatabaseCommandToString(DatabaseQueryCommands::SelectAll))
        .append(TableName)
        .append(" where ")
        .append(TableFieldName)
        .append("=$1");
    try {
      return MCrQuery(TableName, query, std::forward<T>(arg));
    } catch (const std::exception &e) {
      APP_ERROR("ERROR AT GETTABLEDATA2 FUNCTION - " + TableName + " - " +
                std::string(e.what()));
      return {};
    }
  }
  template <typename... Args>
  pqxx::result GetTableData(const std::string &TableName,
                            const std::string &FirstTableFieldName,
                            const std::string &SecondTableFieldName,
                            Args &&...args) {
    std::string query;
    query.append(DatabaseCommandToString(DatabaseQueryCommands::SelectAll))
        .append(TableName)
        .append(" where ")
        .append(FirstTableFieldName)
        .append("=$1")
        .append(" and ")
        .append(SecondTableFieldName)
        .append("=$2");
    try {
      return MCrQuery(TableName, query, std::forward<Args>(args)...);
    } catch (const std::exception &e) {
      APP_ERROR("ERROR AT GETTABLEDATA3 FUNCTION - " + TableName + " - " +
                std::string(e.what()));
      return {};
    }
  }
  pqxx::result DeleteTable(const std::string &TableName,
                           DatabaseQueryCommands QueryCommand);

private:
  bool m_IsConnected;
  std::unique_ptr<DatabaseConnection> m_DatabaseManager;
};

#endif