#include "Core/Location/Geolocation.h"
#include "../../Test.h"

class GeolocationTest : public ::testing::Test {
protected:
  const double latitude = 35.689487;
  const double longitude = 139.691711;
  Geolocation location{latitude, longitude};
};

TEST_F(GeolocationTest, GeolocationPlusCodeTest) {
  auto result = location.GetPlusCode();
  EXPECT_NE(result, "Not Valid");
  EXPECT_FALSE(result.empty());
  EXPECT_GE(result.length(), 8);
}

TEST_F(GeolocationTest, GeolocationCoordinatesTest) {
  auto CoordinatesString = location.GetCoordinatesString();
  auto Coordinates = location.GetCoordinates();
  EXPECT_GT(CoordinatesString.size(), 10);
  EXPECT_DOUBLE_EQ(Coordinates.first, latitude);
  EXPECT_DOUBLE_EQ(Coordinates.second, longitude);
  EXPECT_GE(Coordinates.first, -90.0);
  EXPECT_LE(Coordinates.first, 90.0);
  EXPECT_GE(Coordinates.second, -180.0);
  EXPECT_LE(Coordinates.second, 180.0);
}