#ifndef RESPONSE_H
#define RESPONSE_H

// Entity
// TODO: add logic for the data separation from the full address to entity
// block. INFO: when i get the address from the Address Class, it will be passed
// down to Entity and the logic of the address separation to entities will be
// dealt here, meaning i probably want to change the Entity Ctor to the address
// itself, and the separate to Entities ( Data Structures ). INFO: the address
// class will inherit from entity due to the need use of the private entity
// members and their functionality.

#include "Config/Logger.h"
#include "Core/Benchmark.h"

#include <chrono>
#include <pqxx/pqxx>

template <typename ResType> class Response {
public:
  virtual ~Response() = 0;

  virtual const std::string GetResponseQuery() const = 0;
  virtual const size_t GetResponseSize() const = 0;

  virtual void RunBenchmark(std::function<void()> Func) = 0;
  virtual const std::string ResponseType() = 0;
};

#endif