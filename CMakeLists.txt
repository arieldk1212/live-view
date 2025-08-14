cmake_minimum_required(VERSION 3.5...3.31)
project(live-view VERSION 1.1 LANGUAGES CXX
  DESCRIPTION "Live View"
  HOMEPAGE_URL "https://github.com/arieldk1212/live-view")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INCLUDE_CURRENT_DIR)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_PREFIX_PATH "vcpkg_installed/arm64-osx/share")

include_directories(inc)

find_package(OpenSSL 3.5.2 REQUIRED)
find_package(nlohmann_json 3.12.0 CONFIG REQUIRED)
find_package(flatbuffers CONFIG REQUIRED)

include(FetchContent)
FetchContent_Declare(
  firebase
  GIT_REPOSITORY https://github.com/firebase/firebase-cpp-sdk.git
  GIT_TAG v13.0.0
)
FetchContent_MakeAvailable(firebase)
set(FIREBASE_USE_BUNDLED_DEPS ON)

list(APPEND project_libraries
OpenSSL::SSL
OpenSSL::Crypto
nlohmann_json::nlohmann_json
flatbuffers::flatbuffers
firebase_app
firebase_auth
firebase_database
)

add_subdirectory(src)
enable_testing()
add_subdirectory(tests)

target_link_libraries(src PRIVATE ${project_libraries})
target_link_libraries(tests PRIVATE ${project_libraries})