#ifndef MODEL_H
#define MODEL_H

#include "../Config/DatabaseCommands.h"

#include <pqxx/pqxx>

namespace Model {
class Schemes {
public:
  using SchemeMap = std::unordered_map<std::string, std::string>;

public:
  Schemes();
  ~Schemes() = default;

  [[nodiscard]] SchemeMap GetSchema(const std::string &ModelName) const;

  [[nodiscard]] const std::map<std::string, SchemeMap> &GetSchemes() const {
    return m_Schemes;
  }

private:
  std::map<std::string, SchemeMap> m_Schemes;
};
} // namespace Model

#endif