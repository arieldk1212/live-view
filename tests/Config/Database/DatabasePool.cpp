#include "../../../inc/Config/DatabasePool.h"
#include "../../Test.h"
#include "Models/AddressModel.h"

#include "gtest/gtest.h"
#include <future>
#include <gtest/gtest.h>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <thread>

class DatabasePoolTest : public ::testing::Test {
protected:
  std::unique_ptr<DatabasePool> Manager;

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
        std::make_unique<DatabasePool>(std::move(TestDatabaseConnectionString));
  }

  void SingleThreadTask(int Operations, std::atomic<int> &SuccessfulHits,
                        int AddCounts) {
    for (int i = 0; i < Operations; i++) {
      auto ThreadConn = Manager->GetManagerConnection();
      auto ConnectionStatus = ThreadConn->IsDatabaseConnected();
      EXPECT_TRUE(ConnectionStatus);
      SuccessfulHits++;

      auto ConnectionString = ThreadConn->GetConnectionString();
      EXPECT_FALSE(ConnectionString.empty());
      SuccessfulHits++;

      auto AddressConn = Manager->GetUniqueModelConnection<AddressModel>();
      for (int i = 0; i < AddCounts; i++) {
        AddressConn->Add(ThreadConn, {{"addressname", "hamaasdasdasdasd"},
                                      {"addressnumber", "18"},
                                      {"addresscity", "holon"},
                                      {"addressdistrict", "center"},
                                      {"country", "israel"}});
      }
      SuccessfulHits++;

      Manager->ReturnConnection(ThreadConn);
    }
  }
};

TEST_F(DatabasePoolTest, DatabasePoolGeneralTest) {
  auto conn = Manager->GetManagerConnection();
  auto Status = conn->IsDatabaseConnected();
  auto String = conn->GetConnectionString();
  auto Size = Manager->GetCurrentPoolSize();
  auto MaxSize = Manager->GetPoolLimit();
  Manager->ReturnConnection(conn);
  auto AfterSize = Manager->GetCurrentPoolSize();

  EXPECT_TRUE(Status);
  EXPECT_FALSE(String.empty());
  EXPECT_GT(String.length(), 5);
  EXPECT_EQ(Size, 9);
  EXPECT_EQ(AfterSize, 10);
  EXPECT_EQ(MaxSize, 10);
}

TEST_F(DatabasePoolTest, DatabasePoolLimitTest) {
  auto Connection1 = Manager->GetManagerConnection();
  auto Connection2 = Manager->GetManagerConnection();
  auto Connection3 = Manager->GetManagerConnection();
  auto Connection4 = Manager->GetManagerConnection();
  auto Connection5 = Manager->GetManagerConnection();
  auto Connection6 = Manager->GetManagerConnection();
  auto Connection7 = Manager->GetManagerConnection();
  auto Connection8 = Manager->GetManagerConnection();
  auto Connection9 = Manager->GetManagerConnection();
  auto Connection10 = Manager->GetManagerConnection();

  auto PreSize = Manager->GetCurrentPoolSize();
  Manager->ReturnConnection(Connection1);
  auto AfterSize = Manager->GetCurrentPoolSize();

  EXPECT_FALSE(PreSize);
  EXPECT_NE(PreSize, AfterSize);
}

TEST_F(DatabasePoolTest, DatabasePoolInitModelsTest) {
  Manager->InitModels();

  auto ConnectionTest = Manager->GetManagerConnection();

  auto UniqueAddressModelConn =
      Manager->GetUniqueModelConnection<AddressModel>();

  auto PreData = ConnectionTest->GetModelData("Address");

  UniqueAddressModelConn->Add(ConnectionTest,
                              {{"addressname", "hamaasdasdasdasd"},
                               {"addressnumber", "18"},
                               {"addresscity", "holon"},
                               {"addressdistrict", "center"},
                               {"country", "israel"}});

  auto PostData = ConnectionTest->GetModelData("Address");

  EXPECT_NE(PreData, PostData);
}

TEST_F(DatabasePoolTest, DatabasePoolMethodsTest) {
  auto UniqueModelConn = Manager->GetUniqueModelConnection<AddressModel>();
  auto SharedModelConn = Manager->GetSharedModelConnection<AddressModel>();
  auto UniqueName = UniqueModelConn->GetTableName();
  auto SharedName = SharedModelConn->GetTableName();

  EXPECT_EQ(UniqueName, SharedName);
}

TEST_F(DatabasePoolTest, DatabaseMultiThreadedTest) {
  constexpr int OPERATIONS = 5;
  constexpr int ADD_COUNT = 20;
  constexpr int THREAD_COUNT = 20;
  std::vector<std::thread> Threads;
  std::atomic<int> SuccessfulHits{0};

  Threads.reserve(THREAD_COUNT);
  for (int i = 0; i < THREAD_COUNT; i++) {
    Threads.emplace_back([this, OPERATIONS, &SuccessfulHits, ADD_COUNT]() {
      SingleThreadTask(OPERATIONS, SuccessfulHits, ADD_COUNT);
    });
  }
  for (auto &Thread : Threads) {
    Thread.join();
  }

  EXPECT_EQ(SuccessfulHits, 300);
}