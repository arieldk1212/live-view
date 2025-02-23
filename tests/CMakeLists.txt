enable_testing()
find_package(GTest CONFIG REQUIRED)

add_library(tests
Config/Database/Database.cpp
Config/Config/Config.cpp
Config/Logger/Logger.cpp

Core/UUID.cpp
Core/Location/Geolocation.cpp

Models/AddressModel.cpp
)

add_library(TestLib INTERFACE)
target_link_libraries(TestLib INTERFACE ${PROJECT_LIBRARIES})

include(GoogleTest)

add_executable(DatabaseTest Config/Database/Database.cpp)
add_executable(ConfigTest Config/Config/Config.cpp)
add_executable(LoggerTest Config/Logger/Logger.cpp)
add_executable(UUIDTest Core/UUID.cpp)
add_executable(GeolocationTest Core/Location/Geolocation.cpp)
add_executable(AddressModelTest Models/AddressModel.cpp)

target_link_libraries(DatabaseTest PRIVATE TestLib GTest::gtest_main src)
target_link_libraries(ConfigTest PRIVATE TestLib GTest::gtest_main src)
target_link_libraries(LoggerTest PRIVATE TestLib GTest::gtest_main src)
target_link_libraries(UUIDTest PRIVATE TestLib GTest::gtest_main src)
target_link_libraries(GeolocationTest PRIVATE TestLib GTest::gtest_main src)
target_link_libraries(AddressModelTest PRIVATE TestLib GTest::gtest_main src)

gtest_discover_tests(DatabaseTest)
gtest_discover_tests(ConfigTest)
gtest_discover_tests(LoggerTest)
gtest_discover_tests(UUIDTest)
gtest_discover_tests(GeolocationTest)
gtest_discover_tests(AddressModelTest)