#include "App.h"
#include <firebase/app.h>

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
 */

int main() {

  /**
   * @warning when not in build, debug is in build/src
   * therefore the debugger is in /build/src, the terminal also needs
   * to be there to run without path errors.
   * @attention cmake location is in build/src
   */
  std::filesystem::path ConfigPath = "../../configs/config.json";

  auto DatabaseConnectionString = Config::DatabaseToString(ConfigPath);

  {
    Benchmark Here;
  }
  ::firebase::App *LVApp = ::firebase::App::Create();

  ::firebase::auth::Auth *LVAuth = nullptr;
  ::firebase::database::Database *LVDatabase = nullptr;

  // {
  //   Benchmark Here;
  // }
}