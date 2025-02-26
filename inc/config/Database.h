#ifndef DATABASE_H
#define DATABASE_H

#include "Config/Logger.h"

#include <mutex>
#include <pqxx/pqxx>

using StringUnMap = std::unordered_map<std::string, std::string>;

class DatabaseManager;

/**
 * @warning This header file shouldn't be used directly!
 */
class DatabaseConnection {
public:
  using DatabaseTransaction =
      pqxx::transaction<pqxx::isolation_level::read_committed,
                        pqxx::write_policy::read_write>;

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
  /**
   * @brief overload function for handling user input, improving security
   * issues.
   * @tparam Args
   * @param Query
   * @param args
   * @return pqxx::result
   */
  template <typename... Args>
  pqxx::result CrQuery(const std::string &Query, Args &&...args) {
    if (!IsDatabaseConnected()) {
      APP_ERROR("CRQUERY(PF) - QUERY ERROR - DATABASE CONNECTION ERROR");
      return {};
    }
    try {
      return m_DatabaseNonTransaction.exec_params(Query,
                                                  std::forward<Args>(args)...);
    } catch (const std::exception &e) {
      APP_ERROR("CRQUERY(PF) - QUERY EXECUTION ERROR - " + std::string(e.what()));
      return {};
    }
  }

  /**
   * @brief query function that's based on a base transaction, via the
   * m_DatabaseTransaction, created for write and update operations.
   * @param Query
   * @return pqxx::result
   */
  pqxx::result WQuery(const std::string &Query);

private:
  std::mutex m_DatabaseMutex;
  pqxx::connection m_DatabaseConnection;
  pqxx::nontransaction m_DatabaseNonTransaction;
};

#endif