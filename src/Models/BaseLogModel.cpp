#include "../../inc/Models/BaseLogModel.h"

BaseLogModel::BaseLogModel(std::string &&TableName)
    : m_TableName(std::move(TableName)) {
  APP_INFO("LOGGER MODEL RESOURCE CREATED FOR " + m_TableName);
}

BaseLogModel::~BaseLogModel() {
  APP_CRITICAL("LOGGER MODEL RESOURCE DESTROYED FOR " + m_TableName);
}

pqxx::result BaseLogModel::Add(SharedManager &Manager,
                               const StringUnMap &Fields) {
  return Manager->InsertInto(m_TableName, Fields);
}

LogModel::LogModel() : Model(std::make_unique<BaseLogModel>("Log")) {}

AddressLogModel::AddressLogModel()
    : Model(std::make_unique<BaseLogModel>("AddressLog")) {}