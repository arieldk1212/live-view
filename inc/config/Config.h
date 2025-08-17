#ifndef CONFIG_H
#define CONFIG_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

using Json = nlohmann::json;

class Config {
public:
  inline static Json ReadFile(const std::filesystem::path &Path);
  [[nodiscard]] static std::string
  DatabaseToString(const std::filesystem::path &Path);
  [[nodiscard]] static std::string
  TestDatabaseToString(const std::filesystem::path &Path);
  [[nodiscard]] static std::string
  LoggingPathToString(const std::filesystem::path &Path);
};

#endif