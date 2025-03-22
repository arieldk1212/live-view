#ifndef ADDRESS_MODEL_H
#define ADDRESS_MODEL_H

#include "../Core/Address/Address.h"
#include "../Core/Address/Common/Addresses.h"
#include "../Core/Address/Common/Countries.h"
#include "Model.h"

class AddressModel final {
  /**
   * @brief in here we need to init a logger for a certain address!
   * separate here to entites and make a list inside the model of the data? if
   * yes, how do we extract it?
   */
public:
  AddressModel();
  ~AddressModel();

  [[nodiscard]] const std::string &GetTableName() const { return m_TableName; }

  /**
   * @brief add record to Address table.
   * @param Manager
   * @param Fields
   * @return pqxx::result
   */
  pqxx::result Add(SharedManager &Manager, StringUnMap Fields);

  /**
   * @brief Get the Address ID.
   * @tparam Args
   * @param Manager
   * @param args (addressname, addressnumber)
   * @return std::string
   */
  template <typename... Args>
  [[nodiscard]] std::string GetAddressID(SharedManager &Manager,
                                         Args &&...args) {
    auto Result =
        Manager->GetModelDataArgs(m_TableName, "addressname", "addressnumber",
                                  std::forward<Args>(args)...);
    return Result[0]["addressid"].template as<std::string>();
  }

  /**
   * @brief update a record in the Address table.
   * @tparam T
   * @param Manager
   * @param Fields
   * @param Condition
   * @param arg
   * @return pqxx::result
   */
  template <typename T>
  pqxx::result Update(SharedManager &Manager, const StringUnMap &Fields,
                      const std::string &Condition, T &&arg) {
    pqxx::params params;
    if (Fields.size() == 1) {
      auto field = Fields.begin();
      params.append(field->second);
      params.append(std::forward<T>(arg));
      return Manager->UpdateColumn(m_TableName, field->first, Condition,
                                   params);
    }
    for (const auto &[key, value] : Fields) {
      params.append(value);
    }
    params.append(std::forward<T>(arg));
    return Manager->UpdateColumns(m_TableName, Fields, Condition, params);
  }

  /**
   * @brief delete a record in the Address table.
   * @tparam T
   * @param Manager
   * @param Condition
   * @param arg
   * @return pqxx::result
   */
  template <typename T>
  pqxx::result Delete(SharedManager &Manager, const std::string &Condition,
                      T &&arg) {
    pqxx::params params;
    params.append(std::forward<T>(arg));
    return Manager->DeleteRecord(m_TableName, Condition, params);
  }

  /**
   * @brief Get the Address Data object
   * @param Manager
   * @param ID
   * @return Address
   */
  Address GetAddressData(SharedManager &Manager, const std::string &ID);

private:
  std::string m_TableName;
};

#endif