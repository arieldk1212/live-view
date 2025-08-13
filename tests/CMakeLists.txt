set(CMAKE_PREFIX_PATH "../vcpkg_installed/arm64-osx/share")

enable_testing()
find_package(GTest CONFIG REQUIRED)

add_library(tests
Config/Config/Config.cpp
Config/Logger/Logger.cpp

Core/UUID.cpp
Core/Location/Geolocation.cpp
)

add_library(TestLib INTERFACE)
target_link_libraries(TestLib INTERFACE ${PROJECT_LIBRARIES})

include(GoogleTest)

add_executable(ConfigTest Config/Config/Config.cpp)
add_executable(LoggerTest Config/Logger/Logger.cpp)

add_executable(UUIDTest Core/UUID.cpp)
add_executable(GeolocationTest Core/Location/Geolocation.cpp)

target_link_libraries(ConfigTest PRIVATE TestLib GTest::gtest_main src)
target_link_libraries(LoggerTest PRIVATE TestLib GTest::gtest_main src)

target_link_libraries(UUIDTest PRIVATE TestLib GTest::gtest_main src)
target_link_libraries(GeolocationTest PRIVATE TestLib GTest::gtest_main src)

gtest_discover_tests(ConfigTest)
gtest_discover_tests(LoggerTest)

gtest_discover_tests(UUIDTest)
gtest_discover_tests(GeolocationTest)