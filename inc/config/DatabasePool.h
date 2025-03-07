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
  DatabasePool(std::string &&DatabaseConnectionString);
  ~DatabasePool();

  void InitModels();

  [[nodiscard]] SharedManager GetManagerConnection();
  void ReturnConnection(SharedManager &Connection);

  template <typename ModelClass>
  [[nodiscard]] UniquePtrModel<ModelClass> GetUniqueModelConnection() {
    return std::make_unique<ModelClass>();
  }

  template <typename ModelClass>
  [[nodiscard]] SharedPtrModel<ModelClass> GetSharedModelConnection() {
    return std::make_shared<ModelClass>();
  }

  void RunWQuery(); /* apply a method to run query as pqxx worker */

  [[nodiscard]] int GetPoolLimit();
  [[nodiscard]] int GetCurrentPoolSize();
  [[nodiscard]] const std::string &GetConnectionString();

  std::string ConnectionsReport();
  std::string SingularConsumption(SharedManager &Connection);

private:
  std::mutex m_PoolMutex;
  std::condition_variable m_PoolConditionVariable;

private:
  Model::Schemes m_ModelSchemes;
  const int m_DatabasePoolSize{10};
  std::string m_DatabaseString;
  std::queue<SharedManager> m_DatabasePool;
};

#endif