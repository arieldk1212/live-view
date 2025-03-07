#include "../../inc/Config/DatabaseManager.h"

DatabaseManager::DatabaseManager(
    const std::string &DatabaseConnectionString)
    : m_IsConnected(true) {
  m_DatabaseManager =
      std::make_unique<DatabaseConnection>(DatabaseConnectionString);
  APP_INFO("DATABASE MANAGER CREATED");
}

DatabaseManager::~DatabaseManager() {
  m_DatabaseManager.reset();
  m_IsConnected = false;
  APP_CRITICAL("DATABASE MANAGER DESTROYED");
}

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
  int count = 0;
  std::string query;
  std::string values_count;
  pqxx::params params;
  query.append(DatabaseCommandToString(DatabaseQueryCommands::InsertInto))
      .append(ModelName)
      .append(" (");
  for (const auto &[key, value] : Fields) {
    count += 1;
    query.append(key).append(", ");
    values_count.append("$").append(std::to_string(count)).append(", ");
    params.append(value);
  }
  if (!Fields.empty()) {
    query.pop_back();
    query.pop_back();
    values_count.pop_back();
    values_count.pop_back();
  }
  query.append(") values (").append(values_count).append(")");
  APP_INFO("DATA INSERTED TO TABLE - " + ModelName);
  return MCrQuery(ModelName, query, params);
}

pqxx::result DatabaseManager::UpdateColumn(const std::string &ModelName,
                                           std::string_view FieldName,
                                           std::string_view Condition,
                                           const pqxx::params &Params) {
  std::string query;
  query.append(DatabaseCommandToString(DatabaseQueryCommands::Update))
      .append(ModelName)
      .append(" set ")
      .append(FieldName)
      .append("=$1 where ")
      .append(Condition)
      .append("=$2");
  APP_INFO("COLUMN DATA UPDATED - " + ModelName);
  return MCrQuery(ModelName, query, Params);
}

pqxx::result DatabaseManager::UpdateColumns(const std::string &ModelName,
                                            const StringUnMap &Fields,
                                            std::string_view Condition,
                                            const pqxx::params &Params) {
  int count = 0;
  std::string query;
  query.append(DatabaseCommandToString(DatabaseQueryCommands::Update))
      .append(ModelName)
      .append(" set ");
  for (const auto &[key, value] : Fields) {
    count += 1;
    query.append(key).append("=$").append(std::to_string(count)).append(", ");
  }
  if (!Fields.empty()) {
    query.pop_back();
    query.pop_back();
  }
  query.append(" where ").append(Condition).append("=$").append(
      std::to_string(++count));
  APP_INFO("COLUMNS DATA UPDATED - " + ModelName);
  return MCrQuery(ModelName, query, Params);
}

pqxx::result DatabaseManager::DeleteRecord(const std::string &ModelName,
                                           std::string_view Condition,
                                           const pqxx::params &Params) {
  std::string query;
  query.append("delete from ")
      .append(ModelName)
      .append(" where ")
      .append(Condition)
      .append("=$1");
  APP_INFO("RECORD DATA DELETED IN - " + ModelName);
  return MCrQuery(ModelName, query, Params);
}

pqxx::result DatabaseManager::MCrQuery(const std::string &TableName,
                                       const std::string &Query) {
  try {
    return m_DatabaseManager->CrQuery(Query);
  } catch (pqxx::sql_error const &e) {
    APP_ERROR("MCRQUERY ERROR AT TABLE - " + TableName + " " +
              std::string(e.what()));
    return {};
  } catch (std::exception const &e) {
    APP_ERROR("MCRQUERY GENERAL ERROR - " + std::string(e.what()));
    return {};
  }
}

pqxx::result DatabaseManager::MWQuery(const std::string &TableName,
                                      const std::string &query) {
  try {
    return m_DatabaseManager->WQuery(query);
  } catch (pqxx::sql_error const &e) {
    APP_ERROR("MWQUERY ERROR AT TABLE - " + TableName + " " +
              std::string(e.what()));
    return {};
  } catch (std::exception const &e) {
    APP_ERROR("MWQUERY GENERAL ERROR - " + std::string(e.what()));
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