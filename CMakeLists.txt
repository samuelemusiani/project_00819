cmake_minimum_required(VERSION 3.20)  # CMake version check
project(project_00819)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 11)            # Enable c++14 standard

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# Add main.cpp file of project root directory as source file
add_executable(project_00819 src/main.cpp)

target_link_libraries(project_00819 ${CURSES_LIBRARIES})

