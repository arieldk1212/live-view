cmake_minimum_required(VERSION 3.31)
project(liveView VERSION 1.0 LANGUAGES CXX
  DESCRIPTION "Live View"
  HOMEPAGE_URL "https://github.com/arieldk1212/live-view")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_CURRENT_DIR)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g") # g for lldb help

set(PostgreSQL_ADDITIONAL_VERSIONS "17")

if (APPLE)
  set(CMAKE_TOOLCHAIN_FILE "/Users/$ENV{USER}/vcpkg/scripts/buildsystems/vcpkg.cmake")
  set(CMAKE_PREFIX_PATH "/Users/$ENV{USER}/vcpkg/installed/arm64-osx/share")
endif()

include_directories(inc)

find_package(OpenSSL 3.5.0 REQUIRED)
find_package(PostgreSQL 16.9 REQUIRED)
find_package(spdlog 1.15.3 CONFIG REQUIRED)
find_package(libpqxx 7.10.1 CONFIG REQUIRED)
find_package(aws-c-s3 CONFIG REQUIRED)
find_package(nlohmann_json 3.12.0 CONFIG REQUIRED)


list(APPEND project_libraries
OpenSSL::SSL
OpenSSL::Crypto
libpqxx::pqxx
PostgreSQL::PostgreSQL
AWS::aws-c-s3
spdlog::spdlog
nlohmann_json::nlohmann_json
)

add_subdirectory(src)
enable_testing()
add_subdirectory(tests)

target_link_libraries(src PRIVATE ${project_libraries})
target_link_libraries(tests PRIVATE ${project_libraries})