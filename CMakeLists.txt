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
# MAPS:
file(GLOB_RECURSE SRC_MAPS_FILES src/maps/*.cpp)

# PHYSICS:
file(GLOB_RECURSE SRC_PHYSYCS_FILES src/physics/*.cpp)
list(FILTER SRC_PHYSYCS_FILES EXCLUDE REGEX "test/.*" )

add_executable(game src/main.cpp ${SRC_GAME_FILES} ${SRC_DRAW_FILES} ${SRC_PHYSYCS_FILES} ${SRC_MAPS_FILES})

target_link_libraries(game ${CURSES_LIBRARIES})
target_compile_features(game PRIVATE cxx_std_11)
