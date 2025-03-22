#include "Models/AddressModel.h"
#include "../Test.h"
#include "Config/DatabasePool.h"

class AddressModelTest : public ::testing::Test {
protected:
  std::shared_ptr<DatabaseManager> ManagerConnection;
  std::unique_ptr<DatabasePool> Pool;

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
    ManagerConnection->RemoveModel("Address");
    ManagerConnection.reset();
  }
};

TEST_F(AddressModelTest, AddressCreationTest) {
  auto Address = Pool->GetUniqueModelConnection<AddressModel>();
  auto Result = ManagerConnection->GetModelData(Address->GetTableName());

  EXPECT_NE(Result.columns(), 0);
}

TEST_F(AddressModelTest, AddressTableNameTest) {
  auto Address = Pool->GetUniqueModelConnection<AddressModel>();
  auto Name = Address->GetTableName();

  EXPECT_EQ(Name, "Address");
}

TEST_F(AddressModelTest, AddressAddRecordTest) {
  auto Address = Pool->GetUniqueModelConnection<AddressModel>();

  auto PreData = ManagerConnection->GetModelData("Address");
  Address->Add(ManagerConnection, {{"addressname", "hamaasdasdasdasd"},
                                   {"addressnumber", "18"},
                                   {"addresscity", "holon"},
                                   {"addressdistrict", "center"},
                                   {"country", "israel"}});
  auto PostData = ManagerConnection->GetModelData("Address");

  EXPECT_NE(PreData, PostData);
}

TEST_F(AddressModelTest, AddressUpdateColumnRecordTest) {
  auto Address = Pool->GetUniqueModelConnection<AddressModel>();
  Address->Add(ManagerConnection, {{"addressname", "hamaasdasdasdasd"},
                                   {"addressnumber", "18"},
                                   {"addresscity", "holon"},
                                   {"addressdistrict", "center"},
                                   {"country", "israel"}});

  auto PreData = ManagerConnection->GetModelData("Address");
  Address->Update(ManagerConnection, {{"addressname", "holon"}},
                  "addressnumber", 18);
  auto PostData = ManagerConnection->GetModelData("Address");

  EXPECT_NE(PreData, PostData);
}

TEST_F(AddressModelTest, AddressUpdateColumnsRecordTest) {
  auto Address = Pool->GetUniqueModelConnection<AddressModel>();
  Address->Add(ManagerConnection, {{"addressname", "hamaasdasdasdasd"},
                                   {"addressnumber", "18"},
                                   {"addresscity", "holon"},
                                   {"addressdistrict", "center"},
                                   {"country", "israel"}});

  auto PreData = ManagerConnection->GetModelData("Address");
  Address->Update(ManagerConnection,
                  {{"addressname", "holon"}, {"addressnumber", "20"}},
                  "addressnumber", 18);
  auto PostData = ManagerConnection->GetModelData("Address");

  EXPECT_NE(PreData, PostData);
}

TEST_F(AddressModelTest, AddressDeleteRecordTest) {
  auto Address = Pool->GetUniqueModelConnection<AddressModel>();
  Address->Add(ManagerConnection, {{"addressname", "hamaasdasdasdasd"},
                                   {"addressnumber", "18"},
                                   {"addresscity", "holon"},
                                   {"addressdistrict", "center"},
                                   {"country", "israel"}});

  auto PreData = ManagerConnection->GetModelData("Address");
  Address->Delete(ManagerConnection, "addressnumber", 18);
  auto PostData = ManagerConnection->GetModelData("Address");

  EXPECT_NE(PreData, PostData);
}

TEST_F(AddressModelTest, AddressPerformanceTest) {
  auto Address = Pool->GetUniqueModelConnection<AddressModel>();

  constexpr int LOOPS = 10000;
  std::cout << "Number of Iterations: 10K\n";
  std::cout << "Address Model Add Record Time:\n";
  {
    Benchmark here;
    for (int i = 0; i < LOOPS; i++) {
      Address->Add(ManagerConnection, {{"addressname", "hamaasdasdasdasd"},
                                       {"addressnumber", "18"},
                                       {"addresscity", "holon"},
                                       {"addressdistrict", "center"},
                                       {"country", "israel"}});
    }
  }

  EXPECT_EQ(1, 1);
}

TEST_F(AddressModelTest, AddressAddressTest) {
  auto Address = Pool->GetUniqueModelConnection<AddressModel>();
  Address->Add(ManagerConnection, {{"addressname", "hamaasdasdasdasd"},
                                   {"addressnumber", "18"},
                                   {"addresscity", "holon"},
                                   {"addressdistrict", "center"},
                                   {"country", "israel"}});

  auto AddressID =
      Address->GetAddressID(ManagerConnection, "hamaasdasdasdasd", "18");
  EXPECT_EQ(AddressID.length(), 36);

  auto ValidAddress =
      Address->GetAddressData(ManagerConnection, AddressID).GetAddressValues();

  EXPECT_EQ(ValidAddress["addressid"], AddressID);
  EXPECT_EQ(ValidAddress["addressname"], "hamaasdasdasdasd");
  EXPECT_EQ(ValidAddress["addressnumber"], "18");
  EXPECT_EQ(ValidAddress["addresscity"], "holon");
  EXPECT_EQ(ValidAddress["addressdistrict"], "center");
  EXPECT_EQ(ValidAddress["country"], "israel");
}