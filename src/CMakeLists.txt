list(APPEND sources
App.cpp

Config/Logger.cpp
Config/Config.cpp
Config/Database.cpp
Config/DatabasePool.cpp
Config/DatabaseManager.cpp

Core/UUID.cpp
Core/Image.cpp
Core/Address/Address.cpp
Core/Responses/DatabaseResponse.cpp
Core/Location/Geolocation.cpp
Core/Location/PlusCodes/codearea.cpp
Core/Location/PlusCodes/openlocationcode.cpp

Models/Model.cpp
Models/BaseLogModel.cpp
Models/AddressModel.cpp
)

add_library(src STATIC ${sources})

add_executable(App ${sources})

target_link_libraries(App PRIVATE src ${project_libraries})
target_compile_definitions(App PRIVATE ENABLE_LOGGING)