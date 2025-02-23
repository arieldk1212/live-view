list(APPEND sources
App.cpp

Config/Logger.cpp
Config/Database.cpp
Config/DatabaseManager.cpp
Config/Config.cpp

Core/UUID.cpp
Core/Image.cpp
Core/Location/Geolocation.cpp
Core/Location/PlusCodes/codearea.cpp
Core/Location/PlusCodes/openlocationcode.cpp
Core/Responses/DatabaseResponse.cpp

Models/LogModel.cpp
Models/AddressModel.cpp
)

add_library(src STATIC ${sources})

add_executable(App ${sources})

target_link_libraries(App PRIVATE src ${project_libraries})
target_compile_definitions(App PRIVATE ENABLE_LOGGING)