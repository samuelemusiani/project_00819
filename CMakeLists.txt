cmake_minimum_required(VERSION 3.20)
project(project_00819
	VERSION 0.0.1
	DESCRIPTION "Game written in c++ for the programming course"
	LANGUAGES CXX)


# LIB: ncurses 
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# GAME:
file(GLOB_RECURSE SRC_GAME_FILES src/game/*.cpp)
# DRAW:
file(GLOB_RECURSE SRC_DRAW_FILES src/draw/*.cpp)

add_executable(project_00819_BIN src/main.cpp ${SRC_GAME_FILES} ${SRC_DRAW_FILES})

target_link_libraries(project_00819_BIN ${CURSES_LIBRARIES})
target_compile_features(project_00819_BIN PRIVATE cxx_std_11)
