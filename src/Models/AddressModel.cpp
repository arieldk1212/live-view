#include "../../inc/Models/AddressModel.h"

AddressModel::AddressModel() : m_TableName("Address") {
  APP_INFO("ADDRESS MODEL RESOURCE CREATED");
}

AddressModel::~AddressModel() {
  APP_CRITICAL("ADDRESS MODEL RESOURCE DESTROYED");
}

pqxx::result AddressModel::Add(SharedManager &Manager, StringUnMap Fields) {
  // Fields.emplace("addressdata", "{holon, center, israel}");
  return Manager->InsertInto(m_TableName, Fields);
}

Address AddressModel::GetAddressData(SharedManager &Manager,
                                     const std::string &ID) {
  return Address(Manager, ID);
}