cmake_minimum_required(VERSION 3.12)
project(skfantasy)

set(CMAKE_CC_STANDARD 99)

include(CTest)

add_executable(skfantasy
	src/main.c)

add_library(skcommon STATIC
	src/game.c
	src/colors.c
	src/entity.c
	src/map.c
	src/draw.c
	src/noise.c)

include_directories(include)

if (WIN32  OR MSVC)
	find_library(CURSES pdcurses)
else()
	find_library(CURSES ncurses)
endif()

target_link_libraries(skfantasy PUBLIC ${CURSES} m skcommon)

add_executable(entity_not_null tests/entity_not_null.c)
target_link_libraries(entity_not_null PRIVATE ${CURSES} m skcommon)

add_executable(map_not_null tests/map_not_null.c)
target_link_libraries(map_not_null PRIVATE ${CURSES} m skcommon)

enable_testing()

add_test(
	NAME entity_not_null
	COMMAND $<TARGET_FILE:entity_not_null>
	)

add_test(
	NAME map_not_null
	COMMAND $<TARGET_FILE:map_not_null>
	)
