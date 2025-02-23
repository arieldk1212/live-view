cmake_minimum_required(VERSION 3.24.2)
project(liveView VERSION 1.0 LANGUAGES CXX
  DESCRIPTION "Live View"
  HOMEPAGE_URL "https://github.com/arieldk1212/live-view")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_CURRENT_DIR)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

set(CMAKE_PREFIX_PATH "/usr/local/vcpkg/installed/buildsystems/vcpkg.cmake")

include_directories(inc)
add_subdirectory(src)

find_package(PostgreSQL REQUIRED)
find_package(httplib CONFIG REQUIRED)
find_package(libpqxx CONFIG REQUIRED)

target_link_libraries(src PRIVATE httplib::httplib libpqxx::pqxx PostgreSQL::PostgreSQL)
target_link_libraries(app PRIVATE httplib::httplib libpqxx::pqxx PostgreSQL::PostgreSQL)