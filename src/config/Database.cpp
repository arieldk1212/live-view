#include "../../inc/Config/Database.h"

/**
 * @brief Constructs a DatabaseConnection instance.
 *
 * Initializes the main database connection using the provided connection string and sets up 
 * a non-transactional database object linked to the connection.
 *
 * @param ConnectionString The connection string used to establish the database connection.
 */
DatabaseConnection::DatabaseConnection(const std::string &ConnectionString)
    : m_DatabaseConnection{ConnectionString},
      m_DatabaseNonTransaction{m_DatabaseConnection} {
  APP_INFO("DATABASE CONNECTION CREATED");
}

/**
 * @brief Closes the database connection in a thread-safe manner.
 *
 * This destructor locks a mutex to ensure that closing the connection is thread safe,
 * terminates the active database connection, and logs that the connection has been closed.
 */
DatabaseConnection::~DatabaseConnection() {
  std::lock_guard<std::mutex> lock(m_DatabaseMutex);
  m_DatabaseConnection.close();
  APP_CRITICAL("DATABASE CONNECTION CLOSED");
}

bool DatabaseConnection::IsDatabaseConnected() {
  return m_DatabaseConnection.is_open();
}

/**
 * @brief Executes a SQL query using a non-transactional connection.
 *
 * This method verifies that the database connection is active before executing the provided SQL query.
 * If the connection is not established, it logs an error and returns an empty result. In the event of an
 * exception during execution, the error is logged and an empty result is returned.
 *
 * @param Query The SQL query to execute.
 * @return pqxx::result The result of the executed query, or an empty result if an error occurs.
 */
pqxx::result DatabaseConnection::CrQuery(const std::string &Query) {
  /**
   * @todo need to change this to a concurrent environment. meaning no mutex,
   * init another connection or execute multiple times, test it, check pqxx
   docs.
   * allow multi threaded runs, connection pool??
   * FROM THE PQXX DOCS:
   * Treat a connection, together with any and all objects related to it, as a
   "world" of its own. You should generally make sure that the same "world" is
   never accessed by another thread while you're doing anything non-const in
   there.
   * Not within the same connection. Even if you use nested transactions (see
   the subtransaction class), a connection is always dealing with just one
   transaction at a time. Of course you can create a new transaction on the same
   connection once the previous one has completed. If you want to have multiple
   concurrent transactions, let them work on different connections.
   * for now consider other types of transadction, maybe when pool and
   concurrency is implemented add another features, for one 1 will do with a
   mutex thats not needed but it there.
   https://libpqxx.readthedocs.io/stable/group__transactions.html
   */

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