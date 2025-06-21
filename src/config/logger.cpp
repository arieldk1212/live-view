#include "Config/Logger.h"

std::shared_ptr<spdlog::logger> Logger::s_AppLogger;
std::shared_ptr<spdlog::logger> Logger::s_SystemLogger;

void Logger::Init(const std::string &path) {
  std::string p_Path;
  p_Path = (path == "") ? p_Path = "../../backend-logs/" : p_Path = path;

  spdlog::sink_ptr app_sink =
      std::make_shared<spdlog::sinks::basic_file_sink_mt>(p_Path + "app.log",
                                                          true);
  spdlog::sink_ptr system_sink =
      std::make_shared<spdlog::sinks::basic_file_sink_mt>(p_Path + "sys.log",
                                                          true);

  app_sink->set_pattern("[%T] [%l] %n: %v");
  system_sink->set_pattern("[%T] [%l] %n: %v");

  s_AppLogger = std::make_shared<spdlog::logger>("APP", app_sink);
  s_SystemLogger = std::make_shared<spdlog::logger>("SYSTEM", system_sink);

  spdlog::register_logger(s_AppLogger);
  s_AppLogger->set_level(spdlog::level::trace);
  s_AppLogger->flush_on(spdlog::level::trace);

  spdlog::register_logger(s_SystemLogger);
  s_SystemLogger->set_level(spdlog::level::trace);
  s_SystemLogger->flush_on(spdlog::level::trace);
}
