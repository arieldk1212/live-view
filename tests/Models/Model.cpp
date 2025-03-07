#include "../../inc/Models/Model.h"
#include "../Test.h"

class ModelTest : public ::testing::Test {
protected:
  std::unique_ptr<Model::Schemes> scheme;

  void SetUp() override { scheme = std::make_unique<Model::Schemes>(); }

  void TearDown() override { scheme.reset(); }
};

TEST_F(ModelTest, ModelStatusTest) {
  auto Scheme = scheme->GetSchema("Address");
  auto Result = Scheme.contains("addressid");

  EXPECT_TRUE(Result);
}

TEST_F(ModelTest, ModelSchemesTest) {
  auto Scheme = scheme->GetSchemes();

  EXPECT_TRUE(Scheme.contains("Address"));
}