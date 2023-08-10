# add_library(lib_draw draw.cpp screen.hpp screen.cpp draw.hpp)
target_sources(JumpKing PUBLIC draw.cpp screen.hpp screen.cpp draw.hpp)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

target_link_libraries(JumpKing ${CURSES_LIBRARIES})
