#ifndef DATABASEPOOL_H
#define DATABASEPOOL_H

#include "../Models/Model.h"
#include "DatabaseManager.h"

#include <condition_variable>
#include <queue>

/**
 * @class DatabasePool
 * @todo add logging into database here, each connection will log its status
 * about himself, implement cache, optimize queries per given time, and monitor!
 */

class DatabasePool {
public:
  template <typename Class> using Shared = std::shared_ptr<Class>;
  using SharedManager = Shared<DatabaseManager>;

  template <typename ModelClass>
  using UniquePtrModel = std::unique_ptr<ModelClass>;
  template <typename ModelClass> using SharedPtrModel = Shared<ModelClass>;

public:
  /**
   * @brief Construct a new Database Pool object
   * @param DatabaseConnectionString
   */
  DatabasePool(std::string &&DatabaseConnectionString);
  ~DatabasePool();

  /**
   * @brief Inits the Models in the database, gets a connection, inits, then
   * returns it.
   */
  void InitModels();

  /**
   * @brief Get the Manager Connection object
   * @return SharedManager
   */
  [[nodiscard]] SharedManager GetManagerConnection();
  /**
   * @brief return the connection
   * @param Connection
   */
  void ReturnConnection(SharedManager &Connection);

  /**
   * @brief Get the Unique Model Connection object
   * @tparam ModelClass
   * @return UniquePtrModel<ModelClass>
   */
  template <typename ModelClass>
  [[nodiscard]] UniquePtrModel<ModelClass> GetUniqueModelConnection() {
    return std::make_unique<ModelClass>();
  }
  /**
   * @brief Get the Shared Model Connection object
   * @tparam ModelClass
   * @return SharedPtrModel<ModelClass>
   */
  template <typename ModelClass>
  [[nodiscard]] SharedPtrModel<ModelClass> GetSharedModelConnection() {
    return std::make_shared<ModelClass>();
  }

  void RunWQuery(); /* apply a method to run query as pqxx worker */

  /**
   * @brief Get the Pool Limit object
   * @return int
   */
  [[nodiscard]] int GetPoolLimit();
  /**
   * @brief Get the Current Pool Size object
   * @return int
   */
  [[nodiscard]] int GetCurrentPoolSize();
  /**
   * @brief Get the Connection String object
   * @return const std::string&
   */
  [[nodiscard]] const std::string &GetConnectionString();

  /**
   * @brief returns and outputs the pool connection status.
   * @return std::string
   */
  std::string ConnectionsReport();
  /**
   * @brief returns and outputs a singular connection status.
   * @param Connection
   * @return std::string
   */
  std::string SingularConsumption(SharedManager &Connection);

private:
  std::mutex m_PoolMutex;
  std::mutex m_StatsMutex;
  std::condition_variable m_PoolConditionVariable;

private:
  const int m_DatabasePoolSize{10};
  Model::Schemes m_ModelSchemes;
  std::string m_DatabaseString;
  std::queue<SharedManager> m_DatabasePool;
};

#endif