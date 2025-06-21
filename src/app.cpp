#include "App.h"

/**
 * @attention
 * this acts as the frontend of the application in swift.
 * in this main function we demonstrate how the backend's api is being held.
 * further tests will be run here.
 * maybe instead of main have a function that starts the threading or dbpool,
 * make it a library. communicate with the swift with grpc? graphql? what to
 * choose?? (probably pool for saving and limiting actions). for now act as a
 * int main() application until we reach that bridge..
 */

int main() {

  /**
   * @warning when not in build, debug is in build/src
   * therefore the debugger is in /build/src, the terminal also needs
   * to be there to run without path errors.
   * @attention cmake location is in build/src
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
  {
    Benchmark Here;

    /**
     * @attention should be a shared ptr
     */
    DatabasePool Pool{std::move(DatabaseConnectionString)};

    Pool.InitModels();

    auto ManagerConnection = Pool.GetManagerConnection();

    auto UniqueAddress = Pool.GetUniqueModelConnection<AddressModel>();
    auto UniqueAddressLog = Pool.GetUniqueModelConnection<AddressLogModel>();
    auto UniqueLog = Pool.GetUniqueModelConnection<LogModel>();
    auto UniqueAddressLocation =
        Pool.GetUniqueModelConnection<AddressLocationModel>();

    auto Result = UniqueAddress->Add(ManagerConnection,
                                     {{"addressname", "hamaasdasdasdasd"},
                                      {"addressnumber", "18"},
                                      {"addresscity", "city"},
                                      {"addressdistrict", "center"},
                                      {"country", "ctr"}});

    auto AddressID = UniqueAddress->GetAddressID(ManagerConnection,
                                                 "hamaasdasdasdasd", "18");
    /** @brief if used by lvalue, move it to "Add" function.  */
    UniqueAddressLog->GetModel()->Add(
        ManagerConnection,
        {{"addressid", AddressID}, {"loglevel", "DEBUG"}, {"logmsg", "test"}});

    UniqueAddress->Update(ManagerConnection, {{"addressname", "cityyy"}},
                          "addressnumber", 18);
    UniqueAddress->Update(ManagerConnection,
                          {{"addressname", "hn"}, {"addressnumber", "20"}},
                          "addressnumber", 18);
    /**
     * @brief this illustrated how to add an address location.
    Geolocation AddressLocation{35.652832, 139.839478};
    ManagerConnection->InsertInto(
        "AddressLocation",
        {{"addressid", AddressID},
         {"latitude", std::to_string(AddressLocation.GetCoordinates().first)},
         {"longitude", std::to_string(AddressLocation.GetCoordinates().second)},
         {"pluscode", AddressLocation.GetPlusCode()}});
    */
    /**
     * @todo where will it get the coordinates from? when will it be
     * constructed? -> probably third-party api (google?).
     * the coordiantes will probably get inputted from apple's device via
     * frontend.
     * @todo test the LocationModel.h.. finish implementing and figuring out the
     * solution.
     */
    Geolocation AddressLocation{35.652832, 139.839478};
    UniqueAddressLocation->GetModel()->Add(
        ManagerConnection,
        {{"addressid", AddressID},
         {"latitude", std::to_string(AddressLocation.GetCoordinates().first)},
         {"longitude", std::to_string(AddressLocation.GetCoordinates().second)},
         {"pluscode", AddressLocation.GetPlusCode()}});

    UniqueAddress->Delete(ManagerConnection, "addressnumber", 20);

    UniqueLog->GetModel()->Add(
        ManagerConnection,
        {{"loglevel", "DEBUG"}, {"logmsg", "Test From Main"}});

    ManagerConnection->RemoveModel(
        UniqueAddressLog->GetModel()->GetTableName());
    ManagerConnection->RemoveModel(
        UniqueAddressLocation->GetModel()->GetTableName());
    ManagerConnection->RemoveModel(UniqueAddress->GetTableName());
    ManagerConnection->RemoveModel(UniqueLog->GetModel()->GetTableName());

    Pool.ReturnConnection(ManagerConnection);
  }
}