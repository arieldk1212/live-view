#include "../../inc/Config/Database.h"

DatabaseConnection::DatabaseConnection(const std::string &ConnectionString)
    : m_DatabaseConnection{ConnectionString},
      m_DatabaseNonTransaction{m_DatabaseConnection} {
  APP_INFO("DATABASE CONNECTION CREATED");
}

DatabaseConnection::~DatabaseConnection() {
  std::lock_guard<std::mutex> lock(m_DatabaseMutex);
  m_DatabaseConnection.close();
  APP_CRITICAL("DATABASE CONNECTION CLOSED");
}

bool DatabaseConnection::IsDatabaseConnected() {
  return m_DatabaseConnection.is_open();
}

pqxx::result DatabaseConnection::CrQuery(const std::string &Query) {
  if (!IsDatabaseConnected()) {
    APP_ERROR("CRQUERY - QUERY ERROR - DATABASE CONNECTION ERROR");
    return {};
  }
  try {
    return m_DatabaseNonTransaction.exec(Query);
  } catch (const std::exception &e) {
    APP_ERROR("CRQUERY - QUERY EXECUTION ERROR - " + std::string(e.what()));
    return {};
  }
}

pqxx::result DatabaseConnection::WQuery(const std::string &Query) {
  if (!IsDatabaseConnected()) {
    APP_ERROR("WRQUERY - QUERY ERROR - DATABASE CONNECTION ERROR");
    return {};
  }
  DatabaseTransaction Transaction{m_DatabaseConnection};
  try {
    auto Result = Transaction.exec(Query);
    Transaction.commit();
    return Result;
  } catch (const std::exception &e) {
    Transaction.abort();
    APP_ERROR("WQUERY - QUERY EXECUTION ERROR - " + std::string(e.what()));
    return {};
  }
}