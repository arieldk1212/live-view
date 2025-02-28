#include "../../../inc/Config/DatabasePool.h"
#include "../../Test.h"

#include <future>
#include <memory>
#include <stdio.h>
#include <stdlib.h>

class DatabasePoolTest : public ::testing::Test {
protected:
  std::shared_ptr<DatabasePool> Manager;

  void SetUp() override {
    std::string TestDatabaseConnectionString;
    constexpr int MaxPoolSize = 5;
    if (std::getenv("GITHUB_ACTIONS") != nullptr) {
      TestDatabaseConnectionString =
          Config::TestDatabaseToString("../../configs/ci-config.json");
    } else {
      TestDatabaseConnectionString =
          Config::TestDatabaseToString("../../configs/config.json");
    }
    Manager = std::make_shared<DatabasePool>(
        MaxPoolSize, std::move(TestDatabaseConnectionString));
  }
  void TearDown() override { Manager.reset(); }
};

TEST_F(DatabasePoolTest, DatabasePoolCreationTest) {
  // auto status = Manager->ConnectionsStatus;
  // EXPECT_NE(Before.columns(), After.columns());
}