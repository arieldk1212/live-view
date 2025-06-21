#ifndef LOCATION_MODEL_H
#define LOCATION_MODEL_H

#include "Config/DatabaseManager.h"
#include "Core/Location/Geolocation.h"
#include "Model.h"

/**
 * @todo add Geolocation instance inside? where do i get the coordinates from?
 * test it.
 * @todo when will it be constructed?
 */

class LocationModel {
public:
  LocationModel(std::string &&TableName);
  ~LocationModel();

  [[nodiscard]] const std::string &GetTableName() const { return m_TableName; }

  pqxx::result Add(SharedManager &Manager, const StringUnMap &Fields);

private:
  std::string m_TableName;
};

class AddressLocationModel {
public:
  AddressLocationModel();
  ~AddressLocationModel() = default;

  std::unique_ptr<LocationModel> &GetModel() { return Model; }

private:
  std::unique_ptr<LocationModel> Model;
  // Geolocation ModelLocation;
};

#endif