#ifndef LOG_MODEL_H
#define LOG_MODEL_H

#include "Config/DatabaseManager.h"
#include "Model.h"

class LogModel final {
public:
  LogModel();
  ~LogModel();

  const std::string &GetTableName() const { return m_TableName; }

  pqxx::result Add(const StringUnMap &Fields);

private:
  std::string m_TableName;
};

#endif