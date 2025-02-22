#include "../../../inc/Config/DatabaseManager.h"
#include "../../Test.h"

#include <future>
#include <gtest/gtest.h>
#include <memory>
#include <stdio.h>
#include <stdlib.h>

class DatabaseTest : public ::testing::Test {
protected:
  std::shared_ptr<DatabaseManager> Manager;
  std::shared_ptr<DatabaseManager> Manager1;
  std::shared_ptr<DatabaseManager> Manager2;
  std::string TestTableName;
  StringUnMap TestFieldsFirst;
  StringUnMap TestFieldsSecond;

  /**
   * @brief Sets up the test environment for database operations.
   *
   * Determines the appropriate database connection string based on whether the tests are running
   * within GitHub Actions and initializes three DatabaseManager instances (Manager, Manager1,
   * and Manager2) using that connection string. Also sets the default test table name to "Test".
   */
  void SetUp() override {
    std::string TestDatabaseConnectionString;
    if (std::getenv("GITHUB_ACTIONS") != nullptr) {
      TestDatabaseConnectionString =
          Config::TestDatabaseToString("../../configs/ci-config.json");
    } else {
      TestDatabaseConnectionString =
          Config::TestDatabaseToString("../../configs/config.json");
    }
    Manager1 = std::make_shared<DatabaseManager>(TestDatabaseConnectionString);
    Manager2 = std::make_shared<DatabaseManager>(TestDatabaseConnectionString);
    Manager = std::make_shared<DatabaseManager>(TestDatabaseConnectionString);
    TestTableName = "Test";
  }

  /**
   * @brief Cleans up test fixtures after each test case.
   *
   * This method removes the test models ("Test" and "Test2") from the database, resets the shared pointers 
   * managing database connections, and clears any field definition mappings. It ensures that each test starts 
   * with a clean state.
   */
  void TearDown() override {
    Manager->RemoveModel("Test");
    Manager1->RemoveModel("Test2");
    Manager.reset();
    Manager1.reset();
    Manager2.reset();
    TestFieldsFirst.clear();
    TestFieldsSecond.clear();
  }
};

TEST_F(DatabaseTest, DatabaseModelAddField) {
  TestFieldsFirst.emplace("AddressName", "text");
  Manager->AddModel(TestTableName, TestFieldsFirst);
  auto Before = Manager->GetModelData(TestTableName);
  Manager->AddColumn(TestTableName, "AddedField", "Text");
  auto After = Manager->GetModelData(TestTableName);

  EXPECT_NE(Before.columns(), After.columns());
}

TEST_F(DatabaseTest, DatabaseModelCreateMethodTest) {
  /**
   * @brief can also be written like so ->
   *    TestFieldsFirst.emplace("created_at", "timestamp");
   *    TestFieldsFirst.emplace("addressnumber", "int");
   */
  TestFieldsFirst.insert({
      {"id",
       DatabaseCommandToString(DatabaseFieldCommands::SerialPrimaryKeyField)},
      {"addressname",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100Field)},
      {"addresslocation",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100Field)},
      {"addressnumber",
       DatabaseCommandToString(DatabaseFieldCommands::IntField)},
  });

  auto MethodResponse = Manager->AddModel(TestTableName, TestFieldsFirst);

  EXPECT_NE(MethodResponse.query().size(), 0);
}

TEST_F(DatabaseTest, DatabaseModelGetDataTest) {
  TestFieldsFirst.insert({
      {"id",
       DatabaseCommandToString(DatabaseFieldCommands::SerialPrimaryKeyField)},
      {"addressname",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100Field)},
      {"addresslocation",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100Field)},
      {"addressnumber",
       DatabaseCommandToString(DatabaseFieldCommands::IntField)},
  });

  StringUnMap Data = {{"addressname", "rami"},
                      {"addresslocation", "levi"},
                      {"addressnumber", "18"},
                      {"id", "1"}};

  auto MethodResponse = Manager->AddModel(TestTableName, TestFieldsFirst);
  Manager->InsertInto(TestTableName, Data);
  auto Response = Manager->GetModelData(TestTableName);

  EXPECT_NE(Response.affected_rows(), 0);
}

TEST_F(DatabaseTest, DatabaseModelGetDataByFieldTest) {
  TestFieldsFirst.insert({
      {"id",
       DatabaseCommandToString(DatabaseFieldCommands::SerialPrimaryKeyField)},
      {"addressname",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100Field)},
      {"addresslocation",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100Field)},
      {"addressnumber",
       DatabaseCommandToString(DatabaseFieldCommands::IntField)},
  });

  StringUnMap Data = {{"addressname", "rami"},
                      {"addresslocation", "levi"},
                      {"addressnumber", "18"},
                      {"id", "1"}};

  auto MethodResponse = Manager->AddModel(TestTableName, TestFieldsFirst);
  Manager->InsertInto(TestTableName, Data);
  auto Response = Manager->GetModelData(TestTableName, "id", "1");

  EXPECT_NE(Response.affected_rows(), 0);
}

TEST_F(DatabaseTest, DatabaseTruncateModelTest) {
  TestFieldsFirst.insert({
      {"id",
       DatabaseCommandToString(DatabaseFieldCommands::SerialPrimaryKeyField)},
      {"addressname",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100Field)},
      {"addresslocation",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100Field)},
      {"addressnumber",
       DatabaseCommandToString(DatabaseFieldCommands::IntField)},
  });

  StringUnMap Data = {{"addressname", "rami"},
                      {"addresslocation", "levi"},
                      {"addressnumber", "18"},
                      {"id", "1"}};

  auto MethodResponse = Manager->AddModel(TestTableName, TestFieldsFirst);
  Manager->InsertInto(TestTableName, Data);
  auto Before = Manager->GetModelData(TestTableName);
  auto Response = Manager->TruncateModel(TestTableName);
  auto After = Manager->GetModelData(TestTableName);

  EXPECT_NE(Before, After);
}

TEST_F(DatabaseTest, DatabaseAddColumnTest) {
  TestFieldsFirst.insert({
      {"id",
       DatabaseCommandToString(DatabaseFieldCommands::SerialPrimaryKeyField)},
      {"addressname",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100Field)},
      {"addresslocation",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100Field)},
      {"addressnumber",
       DatabaseCommandToString(DatabaseFieldCommands::IntField)},
  });

  auto MethodResponse = Manager->AddModel(TestTableName, TestFieldsFirst);
  auto Before = Manager->GetModelData(TestTableName);
  Manager->AddColumn(TestTableName, "testfield", "int");
  auto After = Manager->GetModelData(TestTableName);

  EXPECT_NE(Before.columns(), After.columns());
}

TEST_F(DatabaseTest, DatabaseDropColumnTest) {
  TestFieldsFirst.insert({
      {"id",
       DatabaseCommandToString(DatabaseFieldCommands::SerialPrimaryKeyField)},
      {"addressname",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100Field)},
      {"addresslocation",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100Field)},
      {"addressnumber",
       DatabaseCommandToString(DatabaseFieldCommands::IntField)},
  });

  auto MethodResponse = Manager->AddModel(TestTableName, TestFieldsFirst);
  auto Before = Manager->GetModelData(TestTableName);
  Manager->DropColumn(TestTableName, "id");
  auto After = Manager->GetModelData(TestTableName);

  EXPECT_NE(Before.columns(), After.columns());
}

TEST_F(DatabaseTest, DatabaseAlterColumnTest) {
  TestFieldsFirst.insert({
      {"id",
       DatabaseCommandToString(DatabaseFieldCommands::SerialPrimaryKeyField)},
      {"addressname",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100Field)},
      {"addresslocation",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100Field)},
      {"addressnumber",
       DatabaseCommandToString(DatabaseFieldCommands::IntField)},
  });

  StringUnMap PostData = {{"addressname", "20"},
                          {"addresslocation", "levi"},
                          {"addressnumber", "18"},
                          {"id", "1"}};

  auto MethodResponse = Manager->AddModel(TestTableName, TestFieldsFirst);
  auto Before = Manager->GetModelData(TestTableName);
  Manager->AlterColumn(
      TestTableName, "addressname",
      DatabaseCommandToString(DatabaseFieldCommands::IntField));
  Manager->InsertInto(TestTableName, PostData);
  auto After = Manager->GetModelData(TestTableName);

  EXPECT_NE(Before.affected_rows(), After.affected_rows());
}

TEST_F(DatabaseTest, DatabaseInsertIntoTest) {
  TestFieldsFirst.insert({
      {"id",
       DatabaseCommandToString(DatabaseFieldCommands::SerialPrimaryKeyField)},
      {"addressname",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100Field)},
      {"addresslocation",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100Field)},
      {"addressnumber",
       DatabaseCommandToString(DatabaseFieldCommands::IntField)},
  });

  StringUnMap Data = {{"addressname", "rami"},
                      {"addresslocation", "levi"},
                      {"addressnumber", "18"},
                      {"id", "1"}};

  auto MethodResponse = Manager->AddModel(TestTableName, TestFieldsFirst);
  Manager->InsertInto(TestTableName, Data);
  auto Response = Manager->GetModelData(TestTableName);

  EXPECT_NE(Response.affected_rows(), 0);
}

TEST_F(DatabaseTest, DatabaseUpdateColumnTest) {
  TestFieldsFirst.insert({
      {"id",
       DatabaseCommandToString(DatabaseFieldCommands::SerialPrimaryKeyField)},
      {"addressname",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100Field)},
      {"addresslocation",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100Field)},
      {"addressnumber",
       DatabaseCommandToString(DatabaseFieldCommands::IntField)},
  });

  StringUnMap Data = {{"addressname", "rami"},
                      {"addresslocation", "levi"},
                      {"addressnumber", "18"},
                      {"id", "1"}};

  auto MethodResponse = Manager->AddModel(TestTableName, TestFieldsFirst);
  Manager->InsertInto(TestTableName, Data);
  auto PreData = Manager->GetModelData(TestTableName);
  Manager->UpdateColumn(TestTableName, "addressname", "holon", "id=1");
  auto AfterData = Manager->GetModelData(TestTableName);

  EXPECT_NE(AfterData, PreData);
}

TEST_F(DatabaseTest, DatabaseUpdateColumnsTest) {
  TestFieldsFirst.insert({
      {"id",
       DatabaseCommandToString(DatabaseFieldCommands::SerialPrimaryKeyField)},
      {"addressname",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100Field)},
      {"addresslocation",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100Field)},
      {"addressnumber",
       DatabaseCommandToString(DatabaseFieldCommands::IntField)},
  });

  StringUnMap Data = {{"addressname", "rami"},
                      {"addresslocation", "levi"},
                      {"addressnumber", "18"},
                      {"id", "1"}};

  StringUnMap NewFields = {{"addressname", "new"},
                           {"addresslocation", "fields"}};

  auto MethodResponse = Manager->AddModel(TestTableName, TestFieldsFirst);
  Manager->InsertInto(TestTableName, Data);
  auto PreData = Manager->GetModelData(TestTableName);
  Manager->UpdateColumns(TestTableName, NewFields, "id=1");
  auto size = NewFields.size();
  auto AfterData = Manager->GetModelData(TestTableName);

  EXPECT_NE(AfterData, PreData);
}

/**
 * @brief Tests that deleting a record updates the model's data.
 *
 * The test creates a model with specific fields, inserts two records into it, and retrieves
 * the data before deletion. It then deletes one record using a condition ("id=2") and retrieves
 * the data afterwards, ensuring that the deletion has modified the data set.
 */
TEST_F(DatabaseTest, DatabaseDeleteRecordTest) {
  TestFieldsFirst.insert({
      {"id",
       DatabaseCommandToString(DatabaseFieldCommands::SerialPrimaryKeyField)},
      {"addressname",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100Field)},
      {"addresslocation",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100Field)},
      {"addressnumber",
       DatabaseCommandToString(DatabaseFieldCommands::IntField)},
  });

  StringUnMap Data1 = {{"addressname", "rami"},
                       {"addresslocation", "levi"},
                       {"addressnumber", "18"},
                       {"id", "1"}};

  StringUnMap Data2 = {
      {"addressname", "new"}, {"addresslocation", "fields"}, {"id", "2"}};

  auto MethodResponse = Manager->AddModel(TestTableName, TestFieldsFirst);
  Manager->InsertInto(TestTableName, Data1);
  Manager->InsertInto(TestTableName, Data2);
  auto PreData = Manager->GetModelData(TestTableName);
  Manager->DeleteRecord(TestTableName, "id=2");
  auto AfterData = Manager->GetModelData(TestTableName);

  EXPECT_NE(AfterData, PreData);
}

/**
 * @brief Benchmarks performance for key database operations.
 *
 * This test evaluates the performance of database operations using repeated
 * insertions and data retrievals. It sets up a model with a specified schema on
 * two database managers and measures:
 * - The time taken to insert records into the model.
 * - The time taken to retrieve data from a populated model.
 * - The time taken to retrieve data from an empty model.
 *
 * Timing results for each operation are output to the standard output.
 */
TEST_F(DatabaseTest, DatabasePerformanceTest) {
  /**
   * @brief add more features and testing when needed.
   */
  TestFieldsFirst.insert({
      {"id",
       DatabaseCommandToString(DatabaseFieldCommands::SerialPrimaryKeyField)},
      {"addressname",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100Field)},
      {"addressnumber",
       DatabaseCommandToString(DatabaseFieldCommands::IntField)},
  });

  StringUnMap Data = {{"addressname", "rami"},
                      {"addresslocation", "levi"},
                      {"addressnumber", "18"},
                      {"id", "1"}};

  Manager->AddModel(TestTableName, TestFieldsFirst);
  Manager1->AddModel("Test2", TestFieldsFirst);
  constexpr int LOOPS = 10000;
  std::cout << "Insert Into Time:\n";
  {
    Benchmark here;
    for (int i = 0; i < LOOPS; i++) {
      Manager->InsertInto(TestTableName, Data);
    }
  }
  std::cout << "Get Data Time:\n";
  {
    Benchmark here;
    for (int i = 0; i < LOOPS; i++) {
      Manager->GetModelData(TestTableName);
    }
  }
  std::cout << "Get Empty Model Data Time:\n";
  {
    Benchmark andhere;
    for (int i = 0; i < LOOPS; i++) {
      Manager1->GetModelData(TestTableName);
    }
  }

  EXPECT_EQ(1, 1);
}