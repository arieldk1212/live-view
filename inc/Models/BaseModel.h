#ifndef BASE_MODEL_H
#define BASE_MODEL_H

#include "Config/DatabaseManager.h"

#include <nlohmann/json.hpp>
#include <pqxx/pqxx>

using Json = nlohmann::json;

class BaseModel {
public:
  virtual ~BaseModel() = 0;
  virtual const std::string &GetTableName() const = 0;
  virtual pqxx::result Init() = 0;
  virtual pqxx::result Add(StringUnMap Fields) = 0;
  virtual pqxx::result Update(const StringUnMap &Fields,
                              const std::string &Condition) = 0;
  virtual pqxx::result Delete(const std::string &Condition) = 0;

  // virtual Json SerializeModel(const std::string &Data) = 0;
  // virtual std::string DeserializeModel(const Json &JsonData) = 0;
};

#endif