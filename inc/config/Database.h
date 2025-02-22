#ifndef DATABASE_H
#define DATABASE_H

#include "Config/Logger.h"

#include <mutex>
#include <pqxx/pqxx>

using StringUnMap = std::unordered_map<std::string, std::string>;

class DatabaseManager;

/**
 * @brief Executes a SQL query using a non-transactional context.
 *
 * This function runs a SQL query through the m_DatabaseNonTransaction instance,
 * which is optimized for read-only and create operations without requiring full transactional support.
 *
 * @param Query The SQL query string to be executed.
 * @return pqxx::result The result set obtained from executing the query.
 */
class DatabaseConnection {
  /**
   * @warning This header file shouldn't be used directly!
   */
public:
  explicit DatabaseConnection(const std::string &ConnectionString);
  ~DatabaseConnection();

  DatabaseConnection(const DatabaseConnection &) = delete;
  DatabaseConnection &operator=(const DatabaseConnection &) = delete;

  DatabaseConnection(DatabaseConnection &&) noexcept = delete;
  DatabaseConnection &operator=(DatabaseConnection &&) noexcept = delete;

  bool IsDatabaseConnected();

private:
  friend class DatabaseManager;

private:
  /**
   * @brief query function that's based on a nontransaction, via the
   * m_DatabaseNonTransaction, created for read-only and create operations.
   * @param Query
   * @return pqxx::result
   */
  pqxx::result CrQuery(const std::string &Query);

private:
  std::mutex m_DatabaseMutex;
  pqxx::connection m_DatabaseConnection;
  pqxx::nontransaction m_DatabaseNonTransaction;
  // pqxx::transaction<pqxx::isolation_level::read_committed,
  // pqxx::write_policy::read_write>
  // m_DatabaseNonTransaction;
};

#endif