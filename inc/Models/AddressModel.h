#ifndef ADDRESS_MODEL_H
#define ADDRESS_MODEL_H

#include "../Core/Address/Address.h"
#include "BaseModel.h"
#include "Config/DatabaseCommands.h"

class AddressModel final : public BaseModel {
  /**
   * @brief in here we need to init a logger for a certain address!
   * separate here to entites and make a list inside the model of the data? if
   * yes, how do we extract it?
   */
public:
  explicit AddressModel(std::shared_ptr<DatabaseManager> &Manager);
  ~AddressModel() override;

  /**
   * @brief Retrieves the name of the database table associated with the model.
   *
   * This function returns a constant reference to the table name used for storing address-related data.
   *
   * @return const std::string& The name of the database table.
   */
  [[nodiscard]] const std::string &GetTableName() const override {
    return m_TableName;
  }

  pqxx::result Init() override;
  pqxx::result Add(StringUnMap Fields) override;
  pqxx::result Update(const StringUnMap &Fields,
                      const std::string &Condition) override;
  pqxx::result Delete(const std::string &Condition) override;

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