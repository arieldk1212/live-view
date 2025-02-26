#ifndef LOG_MODEL_H
#define LOG_MODEL_H

#include "BaseModel.h"
#include "Config/DatabaseCommands.h"

#include <chrono>

class LogModel final {
public:
  explicit LogModel(std::shared_ptr<DatabaseManager> &Manager);
  ~LogModel();

  const std::string &GetTableName() const { return m_TableName; }

  pqxx::result Init();
  pqxx::result Add(const StringUnMap &Fields);

private:
  std::shared_ptr<DatabaseManager> m_DatabaseManager;

private:
  std::string m_TableName;
  StringUnMap m_LogFields;
};

#endif