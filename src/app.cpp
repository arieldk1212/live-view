#include "../inc/App.h"

/**
 * @attention
 * this acts as the frontend of the application in "swift".
 * in this main function we demonstrate how the backend's api is being held.
 * further tests will be run here.
 * maybe instead of main have a function that starts the threading or dbpool,
 * make it a library. communicate with the swift with grpc? graphql? what to
 * choose?? (probably pool for saving and limiting actions). for now act as a
 * int main() appliaction until we reach that bridge..
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