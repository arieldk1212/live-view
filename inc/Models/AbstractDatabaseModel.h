#ifndef ABSTRACT_DATABASE_MODEL_H
#define ABSTRACT_DATABASE_MODEL_H

#include "../Core/UUID.h"
#include "Config/DatabaseManager.h"

#include <unordered_map>

class AbstractDatabaseModel {
public:
  virtual ~AbstractDatabaseModel() = 0;
  virtual uint64_t GetModelUUID();
  virtual std::string StringSerialization();
  virtual std::string QuerySerialization();
};

template <class T> class Query : public AbstractDatabaseModel {
public:
  Query(const T &FieldType, const T &FieldValue);
  virtual ~Query() override = default;

  void SerializeQuery();

private:
  std::unordered_map<T, T> m_QueryFields; // Example: text -> text value.
  std::string m_QueryString;
};

// INFO: DatabaseModel to basic methods for executing queries, than query
// class to define the fields and relate to a child Specific object
// model to quick insert data, than logger model for example to then execute
// neccessary data into the postgresdb.
// make a query decorator!!!

// TODO: Create basic model -> AbstractModel, then from that create an
// DatabaseModel with basic fields, then we add query for decoration.

#endif