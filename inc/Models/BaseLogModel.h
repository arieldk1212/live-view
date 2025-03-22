#ifndef LOG_MODEL_H
#define LOG_MODEL_H

#include "Config/DatabaseManager.h"
#include "Model.h"

class BaseLogModel {
public:
  BaseLogModel(std::string &&TableName);
  ~BaseLogModel();

  [[nodiscard]] const std::string &GetTableName() const { return m_TableName; }

  pqxx::result Add(SharedManager &Manager, const StringUnMap &Fields);

private:
  std::string m_TableName;
};

class LogModel {
public:
  LogModel();
  ~LogModel() = default;

  std::unique_ptr<BaseLogModel> &GetModel() { return Model; }

private:
  std::unique_ptr<BaseLogModel> Model;
};

class AddressLogModel {
public:
  AddressLogModel();
  ~AddressLogModel() = default;

  std::unique_ptr<BaseLogModel> &GetModel() { return Model; }

private:
  std::unique_ptr<BaseLogModel> Model;
};

#endif