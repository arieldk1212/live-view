#ifndef ADDRESS_MODEL_H
#define ADDRESS_MODEL_H

#include "BaseModel.h"
#include "Config/DatabaseCommands.h"

class AddressModel : BaseModel {
public:
  explicit AddressModel(std::shared_ptr<DatabaseManager> &Manager);
  ~AddressModel() override;

  const std::string GetTableName() const override { return m_TableName; }

  pqxx::result Init() override;
  pqxx::result Add(const StringUnMap &Fields) override;
  // pqxx::result Update(const StringUnMap &Fields) override;
  // pqxx::result Delete(const StringUnMap &Fields) override;

private:
  std::shared_ptr<DatabaseManager> m_DatabaseManager;

private:
  std::string m_TableName;
  StringUnMap m_AddressFields = {
      {"addressname",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100Field)},
      {"addressnumber",
       DatabaseCommandToString(DatabaseFieldCommands::IntField)}};
};

#endif
