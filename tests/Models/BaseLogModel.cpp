#include "Models/BaseLogModel.h"
#include "../Test.h"
#include "Config/DatabasePool.h"
#include "Models/AddressModel.h"

class BaseLogModelTest : public ::testing::Test {
protected:
  std::shared_ptr<DatabaseManager> ManagerConnection;
  std::unique_ptr<DatabasePool> Pool;
  std::array<std::string, 5> DatabaseLogLevels{"DEBUG", "INFO", "WARN", "ERROR",
                                               "CRIT"};

  void SetUp() override {
    std::string DatabaseConnectionString;
    if (std::getenv("GITHUB_ACTIONS") != nullptr) {
      DatabaseConnectionString =
          Config::TestDatabaseToString("../../configs/ci-config.json");
    } else {
      DatabaseConnectionString =
          Config::TestDatabaseToString("../../configs/config.json");
    }
    Pool = std::make_unique<DatabasePool>(std::move(DatabaseConnectionString));
    Pool->InitModels();
    ManagerConnection = Pool->GetManagerConnection();
  }

  void TearDown() override {
    ManagerConnection->RemoveModel("AddressLog");
    ManagerConnection->RemoveModel("Log");
    ManagerConnection.reset();
  }
};

TEST_F(BaseLogModelTest, CreationTest) {
  auto UniqueLog = Pool->GetUniqueModelConnection<LogModel>();
  auto UniqueAddressLog = Pool->GetUniqueModelConnection<AddressLogModel>();

  auto ResultLog =
      ManagerConnection->GetModelData(UniqueLog->GetModel()->GetTableName());
  auto ResultAddressLog = ManagerConnection->GetModelData(
      UniqueAddressLog->GetModel()->GetTableName());

  EXPECT_NE(ResultLog.columns(), 0);
  EXPECT_NE(ResultAddressLog.columns(), 0);
}

TEST_F(BaseLogModelTest, LogAddTest) {
  auto UniqueLog = Pool->GetUniqueModelConnection<LogModel>();

  for (int i = 0; i < DatabaseLogLevels.size(); i++) {
    auto PreData =
        ManagerConnection->GetModelData(UniqueLog->GetModel()->GetTableName());

    UniqueLog->GetModel()->Add(
        ManagerConnection,
        {{"loglevel", DatabaseLogLevels[i]}, {"logmsg", "Test"}});

    auto AfterData =
        ManagerConnection->GetModelData(UniqueLog->GetModel()->GetTableName());

    EXPECT_NE(PreData, AfterData);
  }
}

TEST_F(BaseLogModelTest, AddressLogAddTest) {
  auto UniqueAddress = Pool->GetUniqueModelConnection<AddressModel>();
  auto UniqueAddressLog = Pool->GetUniqueModelConnection<AddressLogModel>();

  auto PreDataAddress =
      ManagerConnection->GetModelData(UniqueAddress->GetTableName());
  UniqueAddress->Add(ManagerConnection, {{"addressname", "hamaasdasdasdasd"},
                                         {"addressnumber", "18"},
                                         {"addresscity", "holon"},
                                         {"addressdistrict", "center"},
                                         {"country", "israel"}});
  auto PostDataAddress =
      ManagerConnection->GetModelData(UniqueAddress->GetTableName());

  EXPECT_NE(PreDataAddress, PostDataAddress);

  auto AddressID =
      UniqueAddress->GetAddressID(ManagerConnection, "hamaasdasdasdasd", "18");
  EXPECT_EQ(AddressID.length(), 36);

  for (int i = 0; i < DatabaseLogLevels.size(); i++) {
    auto PreDataAddressLog = ManagerConnection->GetModelData(
        UniqueAddressLog->GetModel()->GetTableName());

    UniqueAddressLog->GetModel()->Add(ManagerConnection,
                                      {{"addressid", AddressID},
                                       {"loglevel", DatabaseLogLevels[i]},
                                       {"logmsg", "Test"}});

    auto AfterDataAddressLog = ManagerConnection->GetModelData(
        UniqueAddressLog->GetModel()->GetTableName());

    EXPECT_NE(PreDataAddressLog, AfterDataAddressLog);
  }
}