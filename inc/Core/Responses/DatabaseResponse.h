#ifndef DATABASE_RESPONSE_H
#define DATABASE_RESPONSE_H

#include "Response.h"

/**
 * @brief Encapsulates a database response based on pqxx::result.
 *
 * This class wraps a pqxx::result, providing access to the query string and response size,
 * executing benchmarking routines, and identifying the response type as a database response.
 */

/**
 * @brief Initializes a DBResponse with a constant reference to a pqxx::result.
 *
 * @param ResponseData The database response result data.
 */

/**
 * @brief Initializes a DBResponse by moving a pqxx::result.
 *
 * @param ResponseData The database response result data to be moved.
 */

/**
 * @brief Retrieves the query string associated with the response data.
 *
 * @return const std::string The query string from the underlying pqxx::result.
 */

/**
 * @brief Returns the size of the response data.
 *
 * @return const size_t The size of the database response.
 */

/**
 * @brief Executes a provided function for benchmarking purposes.
 *
 * @param Func The callable function to execute as a benchmark.
 */

/**
 * @brief Returns the response type identifier.
 *
 * @return const std::string A string literal "Response: Database" indicating the type.
 */
class DBResponse : Response<pqxx::result> {
public:
  explicit DBResponse(const pqxx::result &ResponseData);
  explicit DBResponse(pqxx::result &&ResponseData);

  [[nodiscard]] const std::string GetResponseQuery() const override {
    return m_ResponseData.query();
  }
  [[nodiscard]] const size_t GetResponseSize() const override {
    return m_ResponseSize;
  }

  void RunBenchmark(std::function<void()> Func) override;
  const std::string ResponseType() override { return "Response: Database"; }

private:
  size_t m_ResponseSize;
  pqxx::result m_ResponseData;
};

/**
 * @brief
 * DBResponse x = Manager->AddModel; -> copy ctor
 * return DBReponse(CreateTable(Args...)); -> ctor
 */

#endif