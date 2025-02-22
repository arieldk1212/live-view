#include "../../inc/Config/DatabaseManager.h"

/**
 * @brief Constructs a new DatabaseManager instance.
 *
 * Initializes the database connection using the provided connection string. If the connection
 * string is empty, a critical error is logged and a std::invalid_argument is thrown. The
 * connection state is set to connected (represented by the integer value 1) and a unique
 * pointer to a DatabaseConnection is created.
 *
 * @param DatabaseConnectionString The non-empty string used to establish the database connection.
 */
DatabaseManager::DatabaseManager(const std::string &DatabaseConnectionString)
    : m_IsConnected(1) {
  if (DatabaseConnectionString.empty()) {
    APP_CRITICAL("DATABASE MANAGER ERROR - EMPTY CONNECTION STRING");
    throw std::invalid_argument("Database Connection String Empty.");
  }
  m_DatabaseConnectionString = DatabaseConnectionString;
  m_DatabaseManager =
      std::make_unique<DatabaseConnection>(m_DatabaseConnectionString);
  APP_INFO("DATABASE MANAGER CREATED");
}

/**
 * @brief Destroys the DatabaseManager and cleans up database resources.
 *
 * Resets the internal database connection, marks the manager as disconnected, and logs the destruction event.
 */
DatabaseManager::~DatabaseManager() {
  m_DatabaseManager.reset();
  m_IsConnected = false;
  APP_CRITICAL("DATABASE MANAGER DESTROYED");
}

/**
 * @brief Checks if the database connection is active.
 *
 * This method returns the current connection status of the database managed by the internal connection object.
 *
 * @return true if the database is connected; false otherwise.
 */
bool DatabaseManager::IsDatabaseConnected() const {
  return m_DatabaseManager->IsDatabaseConnected();
}

/**
 * @brief Serializes model fields into a comma-separated string.
 *
 * This function converts a map of model field names and their associated
 * definitions into a single string formatted as "field1 definition1, field2 definition2, ...".
 * It removes the trailing comma and space if the map is not empty.
 *
 * @param ModelFields A mapping where each key is a model field name and each value is its definition.
 * @return std::string A serialized representation of the model fields suitable for constructing SQL queries.
 */
std::string
DatabaseManager::QuerySerialization(const StringUnMap &ModelFields) {
  std::string Response;
  for (const auto &[key, value] : ModelFields) {
    Response.append(key).append(" ").append(value).append(", ");
  }
  if (!ModelFields.empty()) {
    Response.pop_back();
    Response.pop_back();
  }
  return Response;
}

pqxx::result DatabaseManager::AddModel(const std::string &ModelName,
                                       const StringUnMap &ModelFields) {
  auto Response = CreateTable(ModelName, ModelFields);
  APP_INFO("MODEL ADDED, TABLE CREATED - " + ModelName);
  return Response;
}

pqxx::result DatabaseManager::RemoveModel(const std::string &ModelName) {
  try {
    return DeleteTable(ModelName, DatabaseQueryCommands::DropDrop);
  } catch (const std::exception &e) {
    APP_ERROR("MODEL NOT FOUND - " + std::string(e.what()));
    return {};
  }
}

pqxx::result DatabaseManager::TruncateModel(const std::string &ModelName) {
  return DeleteTable(ModelName, DatabaseQueryCommands::DropTruncate);
}

pqxx::result DatabaseManager::GetModelData(const std::string &ModelName) {
  return GetTableData(ModelName);
}

pqxx::result DatabaseManager::GetModelData(const std::string &ModelName,
                                           const std::string &FieldName,
                                           const std::string &FieldValue) {
  return GetTableData(ModelName, FieldName, FieldValue);
}

pqxx::result DatabaseManager::AddColumn(const std::string &ModelName,
                                        const std::string &FieldName,
                                        const std::string &FieldType) {
  std::string query;
  query.append(DatabaseCommandToString(DatabaseQueryCommands::AlterTable))
      .append(ModelName)
      .append(" add ")
      .append(FieldName)
      .append(" ")
      .append(FieldType)
      .append(";");
  APP_INFO("COLUMN ADDED, TABLE ALTERED - " + ModelName + " - " + FieldName);
  return MCrQuery(ModelName, query);
}

pqxx::result DatabaseManager::DropColumn(const std::string &ModelName,
                                         const std::string &FieldName) {
  std::string query;
  query.append(DatabaseCommandToString(DatabaseQueryCommands::AlterTable))
      .append(ModelName)
      .append(" ")
      .append(DatabaseCommandToString(DatabaseQueryCommands::UpdateDropColumn))
      .append(FieldName);
  APP_INFO("COLUMN DROPED, TABLE ALTERED - " + ModelName + " - " + FieldName);
  return MCrQuery(ModelName, query);
}

pqxx::result DatabaseManager::AlterColumn(const std::string &ModelName,
                                          const std::string &FieldName,
                                          const std::string &NewFieldType) {
  std::string query;
  query.append(DatabaseCommandToString(DatabaseQueryCommands::AlterTable))
      .append(ModelName)
      .append(" ")
      .append(DatabaseCommandToString(DatabaseQueryCommands::AlterColumn))
      .append(FieldName)
      .append(" type ")
      .append(NewFieldType);
  APP_INFO("COLUMN ALTERED, TABLE ALTERED - " + ModelName + " - " + FieldName);
  return MCrQuery(ModelName, query);
}

pqxx::result DatabaseManager::InsertInto(const std::string &ModelName,
                                         const StringUnMap &Fields) {
  std::string query;
  std::string keys;
  std::string values;
  for (const auto &[key, value] : Fields) {
    keys.append(key).append(", ");
    values.append("'").append(value).append("', ");
  }
  if (!Fields.empty()) {
    keys.pop_back();
    keys.pop_back();
    values.pop_back();
    values.pop_back();
  }
  query.append(DatabaseCommandToString(DatabaseQueryCommands::InsertInto))
      .append(ModelName)
      .append(" (")
      .append(keys)
      .append(") values (")
      .append(values)
      .append(");");
  APP_INFO("DATA INSERTED TO TABLE - " + ModelName);
  return MCrQuery(ModelName, query);
}

pqxx::result DatabaseManager::UpdateColumn(const std::string &ModelName,
                                           const std::string &FieldName,
                                           const std::string &NewFieldValue,
                                           const std::string &Condition) {
  std::string query;
  query.append(DatabaseCommandToString(DatabaseQueryCommands::Update))
      .append(ModelName)
      .append(" set ")
      .append(FieldName)
      .append(" = '")
      .append(NewFieldValue)
      .append("' where ")
      .append(Condition)
      .append(";");
  APP_INFO("COLUMN DATA UPDATED - " + ModelName);
  return MCrQuery(ModelName, query);
}

/**
 * @brief Updates multiple columns in the specified model's table.
 *
 * Constructs and executes an SQL UPDATE query for the given model. This method builds a query by iterating over the provided fields mapping—assigning new values to columns—and applies the specified WHERE clause condition to update the matching records.
 *
 * @param ModelName The name of the table corresponding to the model to update.
 * @param Fields A mapping of column names to their new values.
 * @param Condition The SQL condition for selecting records to update.
 * @return pqxx::result The result of executing the update query.
 */
pqxx::result DatabaseManager::UpdateColumns(const std::string &ModelName,
                                            const StringUnMap &Fields,
                                            const std::string &Condition) {
  std::string query;
  query.append(DatabaseCommandToString(DatabaseQueryCommands::Update))
      .append(ModelName)
      .append(" set ");
  for (const auto &[key, value] : Fields) {
    query.append(key).append(" = '").append(value).append("', ");
  }
  query.pop_back();
  query.pop_back();
  query += " where " + Condition + ";";
  APP_INFO("COLUMNS DATA UPDATED - " + ModelName);
  return MCrQuery(ModelName, query);
}

/**
 * @brief Deletes records from the specified model's table based on a condition.
 *
 * Constructs and executes a SQL DELETE query on the table identified by @p ModelName using
 * the provided @p Condition to filter records. Logs the deletion action and performs the query
 * using the MCrQuery function.
 *
 * @param ModelName The name of the table (model) from which records are to be deleted.
 * @param Condition The condition string used in the WHERE clause to determine which records to remove.
 * @return pqxx::result The result of the executed SQL query.
 */
pqxx::result DatabaseManager::DeleteRecord(const std::string &ModelName,
                                           const std::string &Condition) {
  std::string query;
  query.append("delete from ")
      .append(ModelName)
      .append(" where ")
      .append(Condition)
      .append(";");
  APP_INFO("RECORD DATA DELETED IN - " + ModelName);
  return MCrQuery(ModelName, query);
}

/**
 * @brief Executes the specified SQL query and retrieves the result.
 *
 * This method attempts to run the provided SQL query on the database. If a SQL error or any other
 * exception occurs, it logs an error message including the table name and returns an empty result.
 *
 * @param TableName The name of the table used to contextualize error logging.
 * @param query The SQL query to be executed.
 * @return pqxx::result The result of the query execution, or an empty result in case of an error.
 */
pqxx::result DatabaseManager::MCrQuery(const std::string &TableName,
                                       const std::string &query) {
  try {
    auto Response = m_DatabaseManager->CrQuery(query);
    return Response;
  } catch (pqxx::sql_error const &e) {
    APP_ERROR("MCRQUERY ERROR AT TABLE - " + TableName + " " +
              std::string(e.what()));
    return {};
  } catch (std::exception const &e) {
    APP_ERROR("MCRQUERY GENERAL ERROR - " + std::string(e.what()));
    return {};
  }
}

pqxx::result DatabaseManager::CreateTable(const std::string &TableName,
                                          const StringUnMap &TableFields) {
  std::string query;
  query
      .append(DatabaseCommandToString(
          DatabaseQueryCommands::CreateTableIfNotExists))
      .append(TableName)
      .append("(")
      .append(QuerySerialization(TableFields))
      .append(");");
  try {
    return MCrQuery(TableName, query);
  } catch (const std::exception &e) {
    APP_ERROR("ERROR AT CREATETABLE FUNCTION - " + TableName + " - " +
              std::string(e.what()));
    return {};
  }
};

pqxx::result DatabaseManager::GetTableData(const std::string &TableName) {
  std::string query;
  query.append(DatabaseCommandToString(DatabaseQueryCommands::SelectAll))
      .append(TableName);
  try {
    return MCrQuery(TableName, query);
  } catch (const std::exception &e) {
    APP_ERROR("ERROR AT GETTABLEDATA1 FUNCTION - " + TableName + " - " +
              std::string(e.what()));
    return {};
  }
}

pqxx::result DatabaseManager::GetTableData(const std::string &TableName,
                                           const std::string &TableFieldName,
                                           const std::string &TableFieldValue) {
  std::string query;
  query.append(DatabaseCommandToString(DatabaseQueryCommands::SelectAll))
      .append(TableName)
      .append(" where ")
      .append(TableFieldName)
      .append("=")
      .append("'")
      .append(TableFieldValue)
      .append("'");
  try {
    return MCrQuery(TableName, query);
  } catch (const std::exception &e) {
    APP_ERROR("ERROR AT GETTABLEDATA2 FUNCTION - " + TableName + " - " +
              std::string(e.what()));
    return {};
  }
}

/**
 * @brief Executes a SQL command to drop or truncate a table.
 *
 * Constructs a SQL query by appending the string conversion of the specified query command to the table name.
 * If the query command indicates a drop operation (e.g. DatabaseQueryCommands::DropDrop), the table is deleted;
 * otherwise, the table is truncated by removing all records. In case of an exception during query execution,
 * the function logs the error and returns an empty result.
 *
 * @param TableName The name of the table to be modified.
 * @param QueryCommand The command specifying whether to drop or truncate the table.
 * @return pqxx::result The result of the executed query, or an empty result if an error occurred.
 */
pqxx::result DatabaseManager::DeleteTable(const std::string &TableName,
                                          DatabaseQueryCommands QueryCommand) {
  std::string query;
  query.append(DatabaseCommandToString(QueryCommand)).append(TableName);
  try {
    if (std::is_same_v<decltype(QueryCommand),
                       decltype(DatabaseQueryCommands::DropDrop)>)
      APP_INFO("MODEL DELETED, TABLE DELETED - " + TableName);
    else {
      APP_INFO("MODEL MODIFIED, TABLE TRUNCATED - " + TableName);
    }
    return MCrQuery(TableName, query);
  } catch (const std::exception &e) {
    APP_ERROR("ERROR AT DELETETABLE FUNCION - " + TableName + " - " +
              std::string(e.what()));
    return {};
  }
}

/*************************/

// DBManager::DBManager(std::string &&ConnectionString) noexcept
//     : m_DatabaseConntectionPoolSize{1},
//       m_DatabaseConnectionString{std::move(ConnectionString)} {
//   m_DatabaseConnectionPool.emplace_back(
//       std::make_unique<DatabaseManager>(m_DatabaseConnectionString));
// }