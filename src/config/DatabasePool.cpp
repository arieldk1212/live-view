#include "../../inc/Config/DatabasePool.h"

DatabasePool::DatabasePool(std::string &&DatabaseConnectionString)
    : m_DatabaseString(std::move(DatabaseConnectionString)) {
  if (m_DatabaseString.empty()) {
    APP_CRITICAL("DATABASE MANAGER ERROR - EMPTY CONNECTION STRING");
    throw std::invalid_argument("Database Connection String Empty.");
  }
  try {
    std::lock_guard<std::mutex> lock(m_PoolMutex);
    for (int i = 0; i < m_DatabasePoolSize; i++) {
      m_DatabasePool.emplace(
          std::make_shared<DatabaseManager>(m_DatabaseString));
    }
  } catch (const std::exception &e) {
    APP_ERROR("DATABASE POOL CONSTRUCTOR ERROR - " + std::string(e.what()));
  }
  APP_INFO("DATABASE POOL CREATED - NUMBER OF CONNECTIONS: " +
           std::to_string(m_DatabasePoolSize));
}

DatabasePool::~DatabasePool() { APP_CRITICAL("DATABASE POOL DESTROYED"); }

void DatabasePool::InitModels() {
  auto Manager = GetManagerConnection();
  {
    std::scoped_lock<std::mutex> lock(m_PoolMutex);
    for (const auto &[ModelName, Fields] : m_ModelSchemes.GetSchemes()) {
      Manager->AddModel(ModelName, Fields);
    }
    APP_INFO("ALL MODELS TABLES CREATED IN DATABASE");
  }
  ReturnConnection(Manager);
}

SharedManager DatabasePool::GetManagerConnection() {
  std::unique_lock<std::mutex> lock(m_PoolMutex);
  m_PoolConditionVariable.wait(lock,
                               [this]() { return !m_DatabasePool.empty(); });
  auto Connection = std::move(m_DatabasePool.front());
  m_DatabasePool.pop();
  return Connection;
}

void DatabasePool::ReturnConnection(SharedManager &Connection) {
  {
    std::scoped_lock<std::mutex> lock(m_PoolMutex);
    m_DatabasePool.push(std::move(Connection));
  }
  m_PoolConditionVariable.notify_one();
}

int DatabasePool::GetPoolLimit() {
  std::lock_guard<std::mutex> lock(m_StatsMutex);
  return m_DatabasePoolSize;
}

int DatabasePool::GetCurrentPoolSize() {
  std::lock_guard<std::mutex> lock(m_StatsMutex);
  return static_cast<int>(m_DatabasePool.size());
}

const std::string &DatabasePool::GetConnectionString() {
  std::lock_guard<std::mutex> lock(m_StatsMutex);
  return m_DatabaseString;
}

std::string DatabasePool::ConnectionsReport() {
  std::lock_guard<std::mutex> lock(m_StatsMutex);
  int count = 0;
  std::string Status;
  auto Queue = m_DatabasePool;
  while (!Queue.empty()) {
    const auto &Connection = Queue.front();
    Status.append("Connection ")
        .append(std::to_string(++count))
        .append(": Ref Count: ")
        .append(std::to_string(Connection.use_count()))
        .append(", Connection: ")
        .append(std::to_string(Connection->IsDatabaseConnected()))
        .append("\n");
    Queue.pop();
  }
  std::cout << Status << "\n";
  return Status;
}

std::string DatabasePool::SingularConsumption(SharedManager &Connection) {
  std::lock_guard<std::mutex> lock(m_StatsMutex);
  std::cout << "Connection's Ref Count: "
            << std::to_string(Connection.use_count()) << "\n";
  return "Connection's Ref Count: " + std::to_string(Connection.use_count());
}