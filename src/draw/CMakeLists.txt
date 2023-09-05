target_sources(OnlyJump PUBLIC draw.cpp screen.hpp screen.cpp draw.hpp)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

target_link_libraries(OnlyJump ${CURSES_LIBRARIES})
