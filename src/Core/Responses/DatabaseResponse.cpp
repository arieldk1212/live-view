#include "../../../inc/Core/Responses/DatabaseResponse.h"

template <typename ResType> Response<ResType>::~Response() {}

DBResponse::DBResponse(const pqxx::result &ResponseData)
    : m_ResponseData{ResponseData}, m_ResponseSize{sizeof(ResponseData)} {
  APP_INFO("Response Size -> " + std::to_string(m_ResponseSize));
}

DBResponse::DBResponse(pqxx::result &&ResponseData)
    : m_ResponseData{std::move(ResponseData)},
      m_ResponseSize{sizeof(ResponseData)} {
  APP_INFO("Response Size -> " + std::to_string(m_ResponseSize));
}

void DBResponse::RunBenchmark(std::function<void()> Func) {
  Benchmark here;
  Func();
}