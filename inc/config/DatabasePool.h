#ifndef DATABASEPOOL_H
#define DATABASEPOOL_H

#include "DatabaseManager.h"

#include <condition_variable>

/**
 * @class DatabaseConnectionPoolManager
 * @brief this class is reponsible for the database connection pool, in dev.
 * @todo add logging into database here, each connection will log its status
 * about himself, implement cache, fixed number of
 * connections, optimize queries per given time, and monitor!
 */

class DatabasePool {
public:
  template <typename T> using Shared = std::shared_ptr<T>;
  using SharedManager = Shared<DatabaseManager>;

public:
  DatabasePool(int PoolSize, std::string &&DatabaseConnectionString);
  ~DatabasePool();

  inline int GetPoolLimit() const { return m_DatabasePoolSize; }
  inline std::string GetConnectionString() const { return m_DatabaseString; }
  std::string Status(); /* by connection strings? */

  std::optional<SharedManager> GetConnection();
  void Disconnect(); /* dont use this function */

  void Consumptions(); /* status about all connections. */
  void SingularConsumption(SharedManager Connection);

private:
  void Shutdown();

private:
  std::mutex m_PoolMutex;
  std::condition_variable m_PoolConditionVariable;

private:
  int m_DatabasePoolSize;
  std::string m_DatabaseString;
  std::vector<SharedManager> m_DatabasePool;
};

#endif