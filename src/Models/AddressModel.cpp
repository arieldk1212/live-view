#include "../../inc/Models/AddressModel.h"

AddressModel::AddressModel() : m_TableName("Address") {
  APP_INFO("ADDRESS MODEL RESOURCE CREATED");
}

AddressModel::~AddressModel() {
  APP_CRITICAL("ADDRESS MODEL RESOURCE DESTROYED");
}

pqxx::result AddressModel::Add(std::shared_ptr<DatabaseManager> &Manager,
                               StringUnMap Fields) {
  Fields.emplace("entities", "{test1, test2}");

  return Manager->InsertInto(m_TableName, Fields);
}