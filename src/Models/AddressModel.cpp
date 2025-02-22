#include "../../inc/Models/AddressModel.h"

BaseModel::~BaseModel() {}

AddressModel::AddressModel(std::shared_ptr<DatabaseManager> &Manager)
    : m_DatabaseManager(Manager), m_TableName("Address") {
  APP_INFO("ADDRESS MODEL RESOURCE CREATED");
}

AddressModel::~AddressModel() {
  m_DatabaseManager.reset();
  APP_CRITICAL("ADDRESS MODEL RESOURCE DESTROYED");
}

/**
 * @brief Initializes the address table in the database.
 *
 * Registers the address model by invoking the database manager's AddModel method
 * with the table name and associated address fields, and logs a confirmation message.
 *
 * @return pqxx::result The result of the table creation operation.
 */
pqxx::result AddressModel::Init() {
  APP_INFO("ADDRESS TABLE CREATED");
  return m_DatabaseManager->AddModel(m_TableName, m_AddressFields);
}

/**
 * @brief Inserts a new address record into the database.
 *
 * This method appends a default "entities" field with the value "{test1, test2}" to the provided
 * fields and uses the database manager to insert the new record into the address table.
 *
 * @param Fields A mapping of address record fields to their values.
 * @return pqxx::result The result of the insert operation.
 */
pqxx::result AddressModel::Add(StringUnMap Fields) {
  Fields.emplace("entities", "{test1, test2}");

  return m_DatabaseManager->InsertInto(m_TableName, Fields);
}

/**
 * @brief Updates one or more columns in the address table.
 *
 * This method updates address records based on the provided field-value mapping and condition.
 * If the mapping contains a single field, only that column is updated; otherwise, multiple
 * columns are updated simultaneously.
 *
 * @param Fields A mapping of column names to their new values.
 * @param Condition A SQL condition string specifying which records to update.
 * @return pqxx::result The result of the update operation.
 */
pqxx::result AddressModel::Update(const StringUnMap &Fields,
                                  const std::string &Condition) {
  if (Fields.size() == 1) {
    auto field = Fields.begin();
    return m_DatabaseManager->UpdateColumn(m_TableName, field->first,
                                           field->second, Condition);
  }
  return m_DatabaseManager->UpdateColumns(m_TableName, Fields, Condition);
}

/**
 * @brief Deletes records from the Address table that satisfy the specified condition.
 *
 * This function delegates the deletion operation to the DatabaseManager, removing records from the Address table
 * based on the provided SQL condition.
 *
 * @param Condition A SQL expression to filter the records that should be removed.
 * @return pqxx::result The result of the delete operation executed by the DatabaseManager.
 */
pqxx::result AddressModel::Delete(const std::string &Condition) {
  return m_DatabaseManager->DeleteRecord(m_TableName, Condition);
}