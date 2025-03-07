#include "../../../inc/Config/DatabasePool.h"
#include "../../Test.h"

#include <future>
#include <gtest/gtest.h>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <thread>

class DatabasePoolTest : public ::testing::Test {
protected:
  std::shared_ptr<DatabasePool> Manager;

  void SetUp() override {
    std::string TestDatabaseConnectionString;
    if (std::getenv("GITHUB_ACTIONS") != nullptr) {
      TestDatabaseConnectionString =
          Config::TestDatabaseToString("../../configs/ci-config.json");
    } else {
      TestDatabaseConnectionString =
          Config::TestDatabaseToString("../../configs/config.json");
    }
    Manager =
        std::make_shared<DatabasePool>(std::move(TestDatabaseConnectionString));
  }

  void SingleThreadTask(std::string &ModelName) {
    auto ThreadConn = Manager->GetManagerConnection();
    auto ConnectionStatus = ThreadConn->IsDatabaseConnected();
    EXPECT_TRUE(ConnectionStatus);

    auto ConnectionString = ThreadConn->GetConnectionString();
    EXPECT_FALSE(ConnectionString.empty());

    ThreadConn->InsertInto(ModelName, {{"addressname", "hamarganit"}});
  }
};

TEST_F(DatabasePoolTest, DatabasePoolCreationTest) {
  auto conn = Manager->GetManagerConnection();
  auto Status = conn->IsDatabaseConnected();
  auto Result = conn->GetConnectionString();
  Manager->ReturnConnection(conn);

  EXPECT_FALSE(Result.empty());
  EXPECT_GT(Result.length(), 5);
  EXPECT_TRUE(Status);
}

TEST_F(DatabasePoolTest, DatabasePoolTest) {
  auto conn1 = Manager->GetManagerConnection();
  auto conn2 = Manager->GetManagerConnection();
  auto conn3 = Manager->GetManagerConnection();
  auto conn4 = Manager->GetManagerConnection();
  auto conn5 = Manager->GetManagerConnection();
  auto conn6 = Manager->GetManagerConnection();
  auto conn7 = Manager->GetManagerConnection();
  auto conn8 = Manager->GetManagerConnection();
  auto conn9 = Manager->GetManagerConnection();
  auto conn10 = Manager->GetManagerConnection();

  auto size = Manager->GetCurrentPoolSize();

  EXPECT_FALSE(size);
}

// TEST_F(DatabasePoolTest, DatabaseMultiThreadTest) {
//   auto MainConn = Manager->GetManagerConnection();
//   // MainConn->AddModel("address");
//   std::vector<std::thread> Threads;
//   Threads.reserve(20);
//   for (int i = 0; i < 100; i++) {
//     // Threads.emplace_back(SingleThreadTask(),
//     Manager->GetManagerConnection(), )
//   }
// }