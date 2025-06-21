#include "Models/AddressModel.h"

AddressModel::AddressModel() : m_TableName("Address") {
  APP_INFO("ADDRESS MODEL RESOURCE CREATED");
}

AddressModel::~AddressModel() {
  APP_CRITICAL("ADDRESS MODEL RESOURCE DESTROYED");
}

pqxx::result AddressModel::Add(SharedManager &Manager, StringUnMap Fields) {
  auto Country = Fields.at("country");
  auto Address = Fields.at("addressname");

  auto ValidateAddress = Addresses::GetAddress(Address);
  auto ValidateCountry = Countries::GetCountry(Country);

  Addresses::ValidateAddress(ValidateAddress);
  Countries::ValidateCountry(ValidateCountry);

  if (!ValidateAddress && !ValidateCountry) {
    /**
     * @attention in frontend, check for result validation with try.
     */
    return {};
  }

  /**
   * @todo after that, we can change the names or add a field (which will be
   * null as default) with the correct fields, shortname/fullname. maybe even
   * do the same for the number? city? or maybe mix them all up together?
   */

  // Fields.at("addressfullname") = ValidateAddress.FullAddress;
  // Fields.at("country") = ValidateCountry.FullCountry;

  return Manager->InsertInto(m_TableName, Fields);
}

Address AddressModel::GetAddressData(SharedManager &Manager,
                                     const std::string &ID) {
  return Address(Manager, ID);
}