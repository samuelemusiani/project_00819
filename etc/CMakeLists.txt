add_subdirectory(logs)
add_subdirectory(nostd)
add_subdirectory(audio)

target_link_libraries(JumpKing lib_nostd lib_audio lib_logs)
