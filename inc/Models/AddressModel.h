#ifndef ADDRESS_MODEL_H
#define ADDRESS_MODEL_H

#include "../Core/Address/Address.h"
#include "BaseModel.h"
#include "Config/DatabaseCommands.h"

class AddressModel final {
  /**
   * @brief in here we need to init a logger for a certain address!
   * separate here to entites and make a list inside the model of the data? if
   * yes, how do we extract it?
   */
public:
  explicit AddressModel(std::shared_ptr<DatabaseManager> &Manager);
  ~AddressModel();

  [[nodiscard]] const std::string &GetTableName() const { return m_TableName; }

  pqxx::result Init();

  pqxx::result Add(StringUnMap Fields);

  template <typename T>
  pqxx::result Update(const StringUnMap &Fields, const std::string &Condition,
                      T &&arg) {
    pqxx::params params;
    if (Fields.size() == 1) {
      auto field = Fields.begin();
      params.append(field->second);
      params.append(std::forward<T>(arg));
      return m_DatabaseManager->UpdateColumn(m_TableName, field->first,
                                             Condition, params);
    }
    for (const auto &[key, value] : Fields) {
      params.append(value);
    }
    params.append(std::forward<T>(arg));
    return m_DatabaseManager->UpdateColumns(m_TableName, Fields, Condition,
                                            params);
  }

  template <typename T>
  pqxx::result Delete(const std::string &Condition, T &&arg) {
    pqxx::params params;
    params.append(std::forward<T>(arg));
    return m_DatabaseManager->DeleteRecord(m_TableName, Condition, params);
  }

  std::optional<Address> GetEntity(const std::string &Condition);

private:
  std::shared_ptr<DatabaseManager> m_DatabaseManager;

private:
  std::string m_TableName;
  StringUnMap m_AddressFields = {
      {"addressid", DatabaseCommandToString(DatabaseFieldCommands::UUID)},
      {"addressname",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100Field)},
      {"addressnumber",
       DatabaseCommandToString(DatabaseFieldCommands::IntField)},
      {"entities", DatabaseCommandToString(DatabaseFieldCommands::TextArray)}};
};

#endif