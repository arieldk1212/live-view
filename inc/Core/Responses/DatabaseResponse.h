#ifndef DATABASE_RESPONSE_H
#define DATABASE_RESPONSE_H

#include "Response.h"

/**
 * @warning
 * not needed right now, basic pqxx::result solves everything, class is no longer needed and useless.
 */

class DBResponse : public Response<pqxx::result> {
public:
  explicit DBResponse(const pqxx::result &ResponseData);
  explicit DBResponse(pqxx::result &&ResponseData);

  [[nodiscard]] inline std::string GetResponseQuery() const override {
    return m_ResponseData.query();
  }
  [[nodiscard]] inline const size_t GetResponseSize() const override {
    return m_ResponseSize;
  }

  pqxx::result &GetResponseData() { return m_ResponseData; }

  void RunBenchmark(std::function<void()> Func) override;
  const std::string ResponseType() override {
    return "Response Type: Database";
  }

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