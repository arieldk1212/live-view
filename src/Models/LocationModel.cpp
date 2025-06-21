#include "Models/LocationModel.h"

LocationModel::LocationModel(std::string &&TableName)
    : m_TableName(std::move(TableName)) {
  APP_INFO("LOCATION MODEL RESOURCE CREATED FOR " + m_TableName);
}

LocationModel::~LocationModel() {
  APP_CRITICAL("LOCATION MODEL RESOURCE DESTROYED FOR " + m_TableName);
}

pqxx::result LocationModel::Add(SharedManager &Manager,
                                const StringUnMap &Fields) {
  return Manager->InsertInto(m_TableName, Fields);
}

AddressLocationModel::AddressLocationModel()
    : Model(std::make_unique<LocationModel>("AddressLocation")) {}