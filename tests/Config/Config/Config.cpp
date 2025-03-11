#include "../../Test.h"

class ConfigTest : public ::testing::Test {
protected:
    std::string TestDataString;
    std::string DataString;

  void SetUp() override {
    TestDataString = Config::TestDatabaseToString("../../configs/config.json");
    DataString = Config::DatabaseToString("../../configs/config.json");
  }

  void TearDown() override {}
};

TEST_F(ConfigTest, ConfigTestDatabaseString) {
  std::string GoodDataString = "user=arielkriheli password=password "
                                "host=localhost port=5432 dbname=live_view_test";
  EXPECT_EQ(TestDataString, GoodDataString);
}

TEST_F(ConfigTest, ConfigDatabaseString) {
  std::string GoodDataString = "user=arielkriheli password=password "
                                "host=localhost port=5432 dbname=live_view";
  EXPECT_EQ(DataString, GoodDataString);
}