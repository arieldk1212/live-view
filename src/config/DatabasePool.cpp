#include "../../inc/Config/DatabasePool.h"

DatabasePool::DatabasePool(int PoolSize, std::string &&DatabaseConnectionString)
    : m_DatabasePoolSize(PoolSize),
      m_DatabaseString(std::move(DatabaseConnectionString)) {
  if (m_DatabaseString.empty()) {
    APP_CRITICAL("DATABASE MANAGER ERROR - EMPTY CONNECTION STRING");
    throw std::invalid_argument("Database Connection String Empty.");
  }
  try {
    for (int i = 0; i < PoolSize; i++) {
      m_DatabasePool.emplace_back(
          std::make_shared<DatabaseManager>(m_DatabaseString));
    }
  } catch (const std::exception &e) {
    APP_ERROR("DATABASE POOL CONSTRUCTOR ERROR - " + std::string(e.what()));
  }
  APP_INFO("DATABASE POOL CREATED - NUMBER OF CONNECTIONS: " +
           std::to_string(PoolSize));
}

DatabasePool::~DatabasePool() {
  /** @todo add condition variable, if not all resets, wait. */
  Shutdown();
  APP_CRITICAL("DATABASE POOL DESTROYED");
}

void DatabasePool::Shutdown() {
  try {
    for (SharedManager &Connection : m_DatabasePool) {
      Connection.reset();
    }
    m_DatabasePool.clear();
  } catch (const std::exception &e) {
    APP_ERROR("DATABASE POOL SHUTDOWN ERROR - " + std::string(e.what()));
  }
}

std::string DatabasePool::Status() {
  int count = 0;
  std::string Status;
  for (const auto &Connection : m_DatabasePool) {
    Status.append("Connection ")
        .append(std::to_string(++count))
        .append(" - Ref Count: ")
        .append(std::to_string(Connection.use_count()))
        .append(" Connection Status: ")
        .append(std::to_string(Connection->IsDatabaseConnected()))
        .append("\n");
  }
  std::cout << Status;
  return Status;
}

std::optional<DatabasePool::SharedManager> DatabasePool::GetConnection() {
  std::lock_guard<std::mutex> lock(m_PoolMutex);
  for (SharedManager &Connection : m_DatabasePool) {
    if (Connection.use_count() < 2) {
      return Connection;
    }
  }
  return std::nullopt;
}

void DatabasePool::Disconnect() {
  std::lock_guard<std::mutex> lock(m_PoolMutex);
  DatabasePool::~DatabasePool();
}