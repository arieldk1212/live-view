#ifndef MODEL_H
#define MODEL_H

#include "../Config/DatabaseCommands.h"

#include <pqxx/pqxx>

namespace Model {
struct Schemes {
public:
  using SchemeMap = std::unordered_map<std::string, std::string>;

public:
  Schemes();
  ~Schemes() = default;

  [[nodiscard]] SchemeMap GetSchema(const std::string &ModelName) const;

  [[nodiscard]] const std::unordered_map<std::string, SchemeMap> &
  GetSchemes() const {
    return m_Schemes;
  }

private:
  std::unordered_map<std::string, SchemeMap> m_Schemes;
};
}; // namespace Model

#endif