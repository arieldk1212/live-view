#ifndef LOGGER_H
#define LOGGER_H

#include <memory>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <string>

/**
 * @class Logger
 * @brief A static class (singleton) for initializing and accessing application
 * and system loggers.
 */

class Logger {
public:
  /**
   * @brief Initialize the logger with the given path.
   * @param path the directory path to store the log files, if empty, defaults
   * to "../backend-logs/".
   */
  static void Init(const std::string &path);
  static std::shared_ptr<spdlog::logger> &GetAppLogger() { return s_AppLogger; }
  static std::shared_ptr<spdlog::logger> &GetSystemLogger() {
    return s_SystemLogger;
  }

private:
  static std::shared_ptr<spdlog::logger> s_AppLogger;
  static std::shared_ptr<spdlog::logger> s_SystemLogger;
};

/**
 * @brief Via CMakeLists.txt at root directory.
 */
#ifdef ENABLE_LOGGING
#define APP_INFO(...) Logger::GetAppLogger()->info(__VA_ARGS__)
#define APP_TRACE(...) Logger::GetAppLogger()->trace(__VA_ARGS__)
#define APP_DEBUG(...) Logger::GetAppLogger()->debug(__VA_ARGS__)
#define APP_ERROR(...) Logger::GetAppLogger()->error(__VA_ARGS__)
#define APP_WARNING(...) Logger::GetAppLogger()->warn(__VA_ARGS__)
#define APP_CRITICAL(...) Logger::GetAppLogger()->critical(__VA_ARGS__)

#define SYSTEM_INFO(...) Logger::GetSystemLogger()->info(__VA_ARGS__)
#define SYSTEM_TRACE(...) Logger::GetSystemLogger()->trace(__VA_ARGS__)
#define SYSTEM_DEBUG(...) Logger::GetSystemLogger()->debug(__VA_ARGS__)
#define SYSTEM_ERROR(...) Logger::GetSystemLogger()->error(__VA_ARGS__)
#define SYSTEM_WARNING(...) Logger::GetSystemLogger()->warn(__VA_ARGS__)
#define SYSTEM_CRITICAL(...) Logger::GetSystemLogger()->critical(__VA_ARGS__)
#else
#define APP_INFO(...) (void)0
#define APP_TRACE(...) (void)0
#define APP_DEBUG(...) (void)0
#define APP_ERROR(...) (void)0
#define APP_WARNING(...) (void)0
#define APP_CRITICAL(...) (void)0

#define SYSTEM_INFO(...) (void)0
#define SYSTEM_TRACE(...) (void)0
#define SYSTEM_DEBUG(...) (void)0
#define SYSTEM_ERROR(...) (void)0
#define SYSTEM_WARNING(...) (void)0
#define SYSTEM_CRITICAL(...) (void)0
#endif

#endif