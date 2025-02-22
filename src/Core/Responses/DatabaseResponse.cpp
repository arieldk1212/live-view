#include "../../../inc/Core/Responses/DatabaseResponse.h"

template <typename ResType> /**
 * @brief Destructor for the Response template class.
 *
 * This destructor is explicitly defined as empty. It ensures that derived
 * classes can implement their own cleanup logic if necessary without enforcing
 * any specific resource management in the base class.
 */
Response<ResType>::~Response() {}

/**
 * @brief Constructs a DBResponse instance using database query results.
 *
 * This constructor initializes the DBResponse by copying the provided database query
 * result and computing the size of the response data. The resulting size is logged for
 * informational purposes.
 *
 * @param ResponseData A constant reference to a pqxx::result containing the query result.
 */
DBResponse::DBResponse(const pqxx::result &ResponseData)
    : m_ResponseData{ResponseData}, m_ResponseSize{sizeof(ResponseData)} {
  APP_INFO("Response Size -> " + std::to_string(m_ResponseSize));
}

/**
 * @brief Constructs a DBResponse by moving the provided response data.
 *
 * This constructor initializes the DBResponse object by acquiring ownership of the
 * given pqxx::result using move semantics. It also calculates the response size and logs
 * this information for debugging purposes.
 *
 * @param ResponseData An rvalue reference to a pqxx::result containing the database response.
 */
DBResponse::DBResponse(pqxx::result &&ResponseData)
    : m_ResponseData{std::move(ResponseData)},
      m_ResponseSize{sizeof(ResponseData)} {
  APP_INFO("Response Size -> " + std::to_string(m_ResponseSize));
}

/**
 * @brief Executes a provided function within a benchmarking context.
 *
 * This method instantiates a Benchmark object and then executes the supplied callable.
 * It is designed to facilitate performance measurement, though no benchmarking results are returned.
 *
 * @param Func The callable function to be executed.
 */
void DBResponse::RunBenchmark(std::function<void()> Func) {
  Benchmark here;
  Func();
}