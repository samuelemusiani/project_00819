target_sources(JumpKing PUBLIC main.cpp)
# add_executable(JumpKing main.cpp)

add_subdirectory(game)
add_subdirectory(draw)
add_subdirectory(physics)
add_subdirectory(entity)
add_subdirectory(maps)
add_subdirectory(engine)
add_subdirectory(market)

target_link_libraries(JumpKing lib_physics)
