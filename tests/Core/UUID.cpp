#include "../../inc/Core/UUID.h"
#include "../Test.h"

#include <cstddef>
#include <cstdint>

class UUIDTest : public ::testing::Test {
protected:
  const uint64_t test = UUID::GenUUID();
  const uint64_t test2 = UUID::GenUUID();
};

TEST_F(UUIDTest, UUIDValidateType) {
  EXPECT_NE(test, test2);
}

TEST_F(UUIDTest, UUIDVisualValueTest) { 
  EXPECT_EQ(sizeof(test), 8) << test;
}

TEST_F(UUIDTest, UUIDStringTest) { 
  EXPECT_NE(std::to_string(test).size(), 0);
}