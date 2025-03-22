#include "../../inc/Models/AddressModel.h"

AddressModel::AddressModel() : m_TableName("Address") {
  APP_INFO("ADDRESS MODEL RESOURCE CREATED");
}

AddressModel::~AddressModel() {
  APP_CRITICAL("ADDRESS MODEL RESOURCE DESTROYED");
}

pqxx::result AddressModel::Add(SharedManager &Manager, StringUnMap Fields) {
  // Fields.emplace("addressfull", "USA NewYork....");
  auto Address = Fields["addressname"];
  auto Country = Fields["country"];

  auto ValidateAddress = Addresses::GetAddress(Address);
  auto ValidateCountry = Countries::GetCountry(Country);

  Addresses::ValidateAddress(ValidateAddress);
  Countries::ValidateCountry(ValidateCountry);

  if (ValidateAddress && ValidateCountry) {
    /**
     * @todo after that, we can change the names or add a field (which will be
     * null as default) with the correct fields, shortname/fullname. maybe even
     * do the same for the number? city? or maybe mix them all up together?
     */
    return Manager->InsertInto(m_TableName, Fields);
  }
  return {};
}

Address AddressModel::GetAddressData(SharedManager &Manager,
                                     const std::string &ID) {
  return Address(Manager, ID);
}