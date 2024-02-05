cmake_minimum_required(VERSION 3.8)

project(app CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD 20)
find_package(Lua REQUIRED)
include_directories(${LUA_INCLUDE_DIR} libs/)

add_library(graffitiApi src/libGraffiti.cpp)

add_executable(graffiti src/main.cpp)

target_link_libraries(graffitiApi blend2d lua5.4)

target_link_libraries(graffiti blend2d lua5.4 graffitiApi)

install_targets(/bin graffiti)
install(DIRECTORY .graffiti DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
