cmake_minimum_required(VERSION 3.20)
project(
    project_00819
    VERSION 1.0.0
    DESCRIPTION "Game written in c++ for the programming course"
    LANGUAGES CXX)

# LIB: ncurses
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# GAME:
file(GLOB_RECURSE SRC_GAME_FILES src/game/*.cpp)

# DRAW:
file(GLOB_RECURSE SRC_DRAW_FILES src/draw/*.cpp)

# ENGINE
file(GLOB_RECURSE SRC_ENGINE_FILES src/engine/*.cpp)

# MAPS:
file(GLOB_RECURSE SRC_MAPS_FILES src/maps/*.cpp)

# ENTITY:
file(GLOB_RECURSE SRC_ENTITY_FILES src/entity/*.cpp)

# MARKET:
file(GLOB_RECURSE SRC_MARKET_FILES src/market/*.cpp)

# PHYSICS:
file(GLOB_RECURSE SRC_PHYSYCS_FILES src/physics/*.cpp)
list(FILTER SRC_PHYSYCS_FILES EXCLUDE REGEX "test/.*")

# LOGS
file(GLOB_RECURSE ETC_LOGS_FILES etc/logs/*.cpp)

# NOSTD
file(GLOB_RECURSE ETC_NOSTD_FILES etc/nostd/*.cpp)

# NOSTD
file(GLOB_RECURSE ETC_AUDIO_FILES etc/audio/*.cpp)

add_executable(
    game
    src/main.cpp
    ${SRC_GAME_FILES}
    ${SRC_DRAW_FILES}
    ${SRC_ENGINE_FILES}
    ${SRC_PHYSYCS_FILES}
    ${SRC_MAPS_FILES}
    ${ETC_LOGS_FILES}
    ${ETC_NOSTD_FILES}
    ${SRC_ENTITY_FILES}
    ${SRC_MARKET_FILES}
    ${ETC_AUDIO_FILES}
)

target_link_libraries(game ${CURSES_LIBRARIES})
target_compile_features(game PRIVATE cxx_std_14)

if(HACK)
    add_compile_definitions(USE_HACK)
endif(HACK)

if(STD)
    add_compile_definitions(USE_STD_VECTOR)
    add_compile_definitions(USE_STD_STRING)
endif(STD)

if(STD_VECTOR)
    add_compile_definitions(USE_STD_VECTOR)
endif(STD_VECTOR)

if(STD_STRING)
    add_compile_definitions(USE_STD_STRING)
endif(STD_STRING)
