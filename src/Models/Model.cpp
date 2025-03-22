#include "../../inc/Models/Model.h"

namespace Model {
Schemes::Schemes() {
  SchemeMap AddressScheme = {
      {"addressid",
       DatabaseCommandToString(DatabaseFieldCommands::UUIDPrimaryKey)},
      {"addressname",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100NotNullField)},
      {"addressnumber",
       DatabaseCommandToString(DatabaseFieldCommands::IntNotNullField)},
      {"addresscity",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100NotNullField)},
      {"addressdistrict",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100Field)},
      {"country",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100Field)}};
  m_Schemes["Address"] = AddressScheme;

  SchemeMap LogScheme = {
      {"logid",
       DatabaseCommandToString(DatabaseFieldCommands::SerialPrimaryKeyField)},
      {"logtimestamp",
       DatabaseCommandToString(DatabaseFieldCommands::TimestampField)},
      {"loglevel",
       DatabaseCommandToString(DatabaseFieldCommands::LogEnumNotNullField)},
      {"logmsg",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100NotNullField)}};
  m_Schemes["Log"] = LogScheme;

  SchemeMap AddressLogScheme = {
      {"addressid", "uuid"},
      {"", DatabaseCommandToString(DatabaseFieldCommands::FkAddress)},
      {"logtimestamp",
       DatabaseCommandToString(DatabaseFieldCommands::TimestampField)},
      {"loglevel",
       DatabaseCommandToString(DatabaseFieldCommands::LogEnumNotNullField)},
      {"logmsg",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100NotNullField)}};
  m_Schemes["AddressLog"] = AddressLogScheme;
}

Schemes::SchemeMap Schemes::GetSchema(const std::string &ModelName) const {
  auto it = m_Schemes.find(ModelName);
  if (it != m_Schemes.end()) {
    return it->second;
  }
  return {};
}
} // namespace Model
