#ifndef LOG_MODEL_H
#define LOG_MODEL_H

#include "BaseModel.h"
#include "Config/DatabaseCommands.h"

#include <chrono>

class LogModel : public BaseModel {
public:
  explicit LogModel(std::shared_ptr<DatabaseManager> &Manager);
  ~LogModel() override;

  const std::string &GetTableName() const override { return m_TableName; }

  pqxx::result Init() override;
  // pqxx::result Add(const StringUnMap &Fields) override;

private:
  std::shared_ptr<DatabaseManager> m_DatabaseManager;

private:
  std::string m_TableName;
  StringUnMap m_LogFields;
};

#endif