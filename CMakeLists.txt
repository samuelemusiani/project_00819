cmake_minimum_required(VERSION 3.20)
project(
  project_00819
  VERSION 1.0.0
  DESCRIPTION "Game written in c++ for the programming course"
  LANGUAGES C CXX)

add_executable(JumpKing)
add_subdirectory(src)
add_subdirectory(etc)

# if(HACK) add_compile_definitions(USE_HACK) endif(HACK)
#
# if(STD) add_compile_definitions(USE_STD_VECTOR)
# add_compile_definitions(USE_STD_STRING) endif(STD)
#
# if(STD_VECTOR) add_compile_definitions(USE_STD_VECTOR) endif(STD_VECTOR)
#
# if(STD_STRING) add_compile_definitions(USE_STD_STRING) endif(STD_STRING)
