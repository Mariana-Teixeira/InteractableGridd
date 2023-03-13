cmake_minimum_required(VERSION 3.7)

project(Grid)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(Grid "main.cpp" "grid.cpp" "grid.h" "struct.h")
target_link_libraries(Grid ${SDL2_LIBRARIES})