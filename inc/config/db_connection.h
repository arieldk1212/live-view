#ifndef DB_CONNECTION_H
#define DB_CONNECTION_H

#include <memory>
#include <pqxx/pqxx>

#include "config/logger.h"

namespace DB {

typedef std::map<std::string, std::string> DBInfo;
typedef std::shared_ptr<pqxx::connection> DBPtr;

class DBConnection {
public:
  DBConnection();

  DBConnection(DBConnection&& ) = delete;
  DBConnection(const DBConnection& other) = delete;
  DBConnection& operator=(DBConnection&& ) = delete;
  DBConnection& operator=(const DBConnection& other) = delete;

private:
  DBPtr m_DBConnection;
  DBInfo m_ConnectionInfo;
  std::string m_ConnectionString;
};
}

#endif