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

pqxx::result AddressModel::Init() {
  APP_INFO("ADDRESS TABLE CREATED");
  return m_DatabaseManager->AddModel(m_TableName, m_AddressFields);
}

pqxx::result AddressModel::Add(StringUnMap Fields) {
  Fields.emplace("entities", "{test1, test2}");

  return m_DatabaseManager->InsertInto(m_TableName, Fields);
}

pqxx::result AddressModel::Update(const StringUnMap &Fields,
                                  const std::string &Condition) {
  if (Fields.size() == 1) {
    auto field = Fields.begin();
    return m_DatabaseManager->UpdateColumn(m_TableName, field->first,
                                           field->second, Condition);
  }
  return m_DatabaseManager->UpdateColumns(m_TableName, Fields, Condition);
}

pqxx::result AddressModel::Delete(const std::string &Condition) {
  return m_DatabaseManager->DeleteRecord(m_TableName, Condition);
}