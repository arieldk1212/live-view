#include "../inc/App.h"

/**
 * @brief Application entry point demonstrating initialization and basic CRUD operations.
 *
 * Initializes logging and establishes a database connection using settings from a configuration file.
 * Sets up a shared database manager and an address model, then performs demonstration operations:
 * adding, updating, and deleting address entries. Cleanup is executed by removing the address model
 * from the manager.
 *
 * @warning When running in debug mode, ensure the working directory is correctly set (e.g., to build/src)
 * to avoid path-related errors.
 *
 * @attention This function serves as the frontend interface of the application and may be refactored in the
 * future to support features such as threading, database pooling, or alternate communication methods like gRPC/GraphQL.
 */

int main() {

  /**
   * @warning when not in build, debug is in build/src
   * therefore the debugger is in /build/src, the terminal also needs
   * to be there to run without path errors.
   */
  std::filesystem::path ConfigPath = "../../configs/config.json";

  Logger::Init(Config::LoggingPathToString(ConfigPath));
  auto DatabaseConnectionString = Config::DatabaseToString(ConfigPath);

  APP_INFO("APP LOGGER INITIALIZED");
  SYSTEM_INFO("SYSTEM LOGGER INITIALIZED");

  APP_INFO("APP INITIALIZED");
  SYSTEM_INFO("SYSTEM INITIALIZED");

  /**
   * @attention
   * can be set to unique_ptr, but can't create models with it, can
   * be used for fast managing actions. for modeling, use shared_ptr.
   */
  auto Manager = std::make_shared<DatabaseManager>(DatabaseConnectionString);
  AddressModel Addresses(Manager);
  Addresses.Init();
  auto Result = Addresses.Add(
      {{"addressname", "hamaasdasdasdasd"}, {"addressnumber", "18"}});
  Addresses.Update({{"addressname", "holon"}}, "addressnumber=18");
  Addresses.Update({{"addressname", "hn"}, {"addressnumber", "20"}},
                   "addressnumber=18");
  Addresses.Delete("addressnumber=20");

  Manager->RemoveModel(Addresses.GetTableName());
}