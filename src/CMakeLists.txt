list(APPEND sources
App.cpp

Config/Config.cpp

Core/UUID.cpp
Core/Image.cpp
Core/Location/Geolocation.cpp
Core/Location/PlusCodes/codearea.cpp
Core/Location/PlusCodes/openlocationcode.cpp

)

add_library(src STATIC ${sources})

add_executable(App ${sources})

target_link_libraries(App PRIVATE src ${project_libraries})
target_compile_definitions(App PRIVATE ENABLE_LOGGING)