#include "../../inc/Models/Model.h"

namespace Model {
Schemes::Schemes() {
  SchemeMap AddressScheme = {
      {"addressid", DatabaseCommandToString(DatabaseFieldCommands::UUID)},
      {"addressname",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100Field)},
      {"addressnumber",
       DatabaseCommandToString(DatabaseFieldCommands::IntField)},
      {"entities", DatabaseCommandToString(DatabaseFieldCommands::TextArray)}};

  m_Schemes["Address"] = AddressScheme;
}

Schemes::SchemeMap Schemes::GetSchema(const std::string &ModelName) const {
  auto it = m_Schemes.find(ModelName);
  if (it != m_Schemes.end()) {
    return it->second;
  }
  return {};
}
}; // namespace Model
