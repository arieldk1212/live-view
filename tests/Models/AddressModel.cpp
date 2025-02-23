#include "../../inc/Models/AddressModel.h"
#include "../Test.h"

class AddressModelTest : public ::testing::Test {
protected:
  std::string DatabaseConnectionString;
  std::shared_ptr<DatabaseManager> Manager;

  void SetUp() override {
    if (std::getenv("GITHUB_ACTIONS") != nullptr) {
      DatabaseConnectionString =
          Config::TestDatabaseToString("../../configs/ci-config.json");
    } else {
      DatabaseConnectionString =
          Config::TestDatabaseToString("../../configs/config.json");
    }
    Manager = std::make_shared<DatabaseManager>(DatabaseConnectionString);
  }

  void TearDown() override {
    Manager->RemoveModel("Address");
    Manager.reset();
  }
};

TEST_F(AddressModelTest, AddressCreationTest) {
  AddressModel Address(Manager);
  Address.Init();
  auto Result = Manager->GetModelData(Address.GetTableName());

  EXPECT_NE(Result.columns(), 0);
}

TEST_F(AddressModelTest, AddressTableNameTest) {
  AddressModel Address(Manager);
  auto Name = Address.GetTableName();

  EXPECT_EQ(Name, "Address");
}

TEST_F(AddressModelTest, AddressAddRecordTest) {
  AddressModel Address(Manager);
  Address.Init();

  auto PreData = Manager->GetModelData("Address");
  Address.Add({{"addressname", "hamaasdasdasdasd"}, {"addressnumber", "18"}});
  auto PostData = Manager->GetModelData("Address");

  EXPECT_NE(PreData, PostData);
}

TEST_F(AddressModelTest, AddressUpdateColumnRecordTest) {
  AddressModel Address(Manager);
  Address.Init();
  Address.Add({{"addressname", "hamaasdasdasdasd"}, {"addressnumber", "18"}});

  auto PreData = Manager->GetModelData("Address");
  Address.Update({{"addressname", "holon"}}, "addressnumber=18");
  auto PostData = Manager->GetModelData("Address");

  EXPECT_NE(PreData, PostData);
}

TEST_F(AddressModelTest, AddressUpdateColumnsRecordTest) {
  AddressModel Address(Manager);
  Address.Init();
  Address.Add({{"addressname", "hamaasdasdasdasd"}, {"addressnumber", "18"}});

  auto PreData = Manager->GetModelData("Address");
  Address.Update({{"addressname", "holon"}, {"addressnumber", "20"}},
                 "addressnumber=18");
  auto PostData = Manager->GetModelData("Address");

  EXPECT_NE(PreData, PostData);
}

TEST_F(AddressModelTest, AddressDeleteRecordTest) {
  AddressModel Address(Manager);
  Address.Init();
  Address.Add({{"addressname", "hamaasdasdasdasd"}, {"addressnumber", "18"}});

  auto PreData = Manager->GetModelData("Address");
  Address.Delete("addressnumber=18");
  auto PostData = Manager->GetModelData("Address");

  EXPECT_NE(PreData, PostData);
}