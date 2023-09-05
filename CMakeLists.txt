cmake_minimum_required(VERSION 3.20)
project(
  project_00819
  VERSION 1.0.0
  DESCRIPTION "Game written in c++ for the programming course"
  LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)

add_executable(OnlyJump)
add_subdirectory(src)
add_subdirectory(etc)

if(HACK)
  add_compile_definitions(USE_HACK)
endif(HACK)
