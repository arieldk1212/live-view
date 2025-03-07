#ifndef RESPONSE_H
#define RESPONSE_H

#include "Config/Logger.h"
#include "Core/Benchmark.h"

#include <chrono>
#include <pqxx/pqxx>

template <typename ResType> class Response {
public:
  virtual ~Response() = 0;

  virtual std::string GetResponseQuery() const = 0;
  virtual const size_t GetResponseSize() const = 0;

  virtual void RunBenchmark(std::function<void()> Func) = 0;
  virtual const std::string ResponseType() = 0;
};

#endif