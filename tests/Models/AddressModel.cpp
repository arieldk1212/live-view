#include "../../inc/Models/AddressModel.h"
#include "../../inc/Config/DatabasePool.h"
#include "../Test.h"

class AddressModelTest : public ::testing::Test {
protected:
  std::shared_ptr<DatabaseManager> Manager;
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
    Manager = Pool->GetManagerConnection();
  }

  void TearDown() override {
    Manager->RemoveModel("Address");
    Manager.reset();
  }
};

TEST_F(AddressModelTest, AddressCreationTest) {
  AddressModel Address;
  auto Result = Manager->GetModelData(Address.GetTableName());

  EXPECT_NE(Result.columns(), 0);
}

TEST_F(AddressModelTest, AddressTableNameTest) {
  AddressModel Address;
  auto Name = Address.GetTableName();

  EXPECT_EQ(Name, "Address");
}

TEST_F(AddressModelTest, AddressAddRecordTest) {
  AddressModel Address;

  auto PreData = Manager->GetModelData("Address");
  Address.Add(Manager,
              {{"addressname", "hamaasdasdasdasd"}, {"addressnumber", "18"}});
  auto PostData = Manager->GetModelData("Address");

  EXPECT_NE(PreData, PostData);
}

TEST_F(AddressModelTest, AddressUpdateColumnRecordTest) {
  AddressModel Address;
  Address.Add(Manager,
              {{"addressname", "hamaasdasdasdasd"}, {"addressnumber", "18"}});

  auto PreData = Manager->GetModelData("Address");
  Address.Update(Manager, {{"addressname", "holon"}}, "addressnumber", 18);
  auto PostData = Manager->GetModelData("Address");

  EXPECT_NE(PreData, PostData);
}

TEST_F(AddressModelTest, AddressUpdateColumnsRecordTest) {
  AddressModel Address;
  Address.Add(Manager,
              {{"addressname", "hamaasdasdasdasd"}, {"addressnumber", "18"}});

  auto PreData = Manager->GetModelData("Address");
  Address.Update(Manager, {{"addressname", "holon"}, {"addressnumber", "20"}},
                 "addressnumber", 18);
  auto PostData = Manager->GetModelData("Address");

  EXPECT_NE(PreData, PostData);
}

TEST_F(AddressModelTest, AddressDeleteRecordTest) {
  AddressModel Address;
  Address.Add(Manager,
              {{"addressname", "hamaasdasdasdasd"}, {"addressnumber", "18"}});

  auto PreData = Manager->GetModelData("Address");
  Address.Delete(Manager, "addressnumber", 18);
  auto PostData = Manager->GetModelData("Address");

  EXPECT_NE(PreData, PostData);
}

TEST_F(AddressModelTest, AddressPerformanceTest) {
  AddressModel Address;

  constexpr int LOOPS = 10000;
  std::cout << "Number of Iterations: 10K\n";
  std::cout << "Address Model Add Record Time:\n";
  {
    Benchmark here;
    for (int i = 0; i < LOOPS; i++) {
      Address.Add(Manager, {{"addressname", "hamaasdasdasdasd"},
                            {"addressnumber", "18"}});
    }
  }

  EXPECT_EQ(1, 1);
}