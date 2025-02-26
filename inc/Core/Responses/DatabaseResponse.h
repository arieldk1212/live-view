#ifndef DATABASE_RESPONSE_H
#define DATABASE_RESPONSE_H

#include "Response.h"

class DBResponse : public Response<pqxx::result> {
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