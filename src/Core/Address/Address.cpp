#include "../../../inc/Core/Address/Address.h"

Address::Address(SharedManager &Manager, std::string IDQuery) {
  auto Result = Manager->GetModelData("Address", "addressid", IDQuery);
  if (!Result.empty()) {
    for (int i = 0; i < Result.columns(); i++) {
      m_AddressData.insert(
          {Result.column_name(i), Result[0][i].as<std::string>()});
    }
  }
}