cmake_minimum_required(VERSION 3.20)
project(game_class)
set(CMAKE_CXX_STANDARD 11)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(game_class game.cpp)

target_link_libraries(game_class ${CURSES_LIBRARIES})
