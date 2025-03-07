#include "../../inc/Models/LogModel.h"

LogModel::LogModel() : m_TableName("Log") {
  APP_INFO("LOGGER MODEL RESOURCE CREATED");
}

LogModel::~LogModel() {
  APP_CRITICAL("LOGGER MODEL RESOURCE DESTYOYED");
}