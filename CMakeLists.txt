cmake_minimum_required(VERSION 3.12)
project(skfantasy)

set(CMAKE_CC_STANDARD 99)

add_executable(skfantasy
	src/main.c
	src/noise.c
	src/draw.c
	src/map.c
	src/entity.c
	src/colors.c
	src/game.c)

include_directories(include)

if (WIN32  OR MSVC)
	find_library(CURSES pdcurses)
else()
	find_library(CURSES ncurses)
endif()

target_link_libraries(skfantasy PUBLIC ${CURSES} m)
