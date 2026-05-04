cmake_minimum_required(VERSION 3.10)
project(skfantasy VERSION 0.3.2)

# -------------------------------------------------------------------
#  Version string – matches the original "v0.3.2" format
# -------------------------------------------------------------------
set(VERSION_STRING "v${PROJECT_VERSION}")

# -------------------------------------------------------------------
#  Generate compile_commands.json for clangd
# -------------------------------------------------------------------
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -------------------------------------------------------------------
#  Place the executable directly into linux_pkg/
# -------------------------------------------------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/linux_pkg)

# -------------------------------------------------------------------
#  Find all source files (with CONFIGURE_DEPENDS to detect new files)
# -------------------------------------------------------------------
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*.c")

# -------------------------------------------------------------------
#  Executable
# -------------------------------------------------------------------
add_executable(skfantasy ${SRC_FILES})

# -------------------------------------------------------------------
#  Dependencies via pkg-config (ncurses, guile-3.0)
# -------------------------------------------------------------------
find_package(PkgConfig REQUIRED)
pkg_check_modules(NCURSES REQUIRED ncurses)
pkg_check_modules(GUILE  REQUIRED guile-3.0)

# Include paths (local and from pkg-config)
target_include_directories(skfantasy PRIVATE
    include
    ${NCURSES_INCLUDE_DIRS}
    ${GUILE_INCLUDE_DIRS}
)

# Compiler flags from pkg-config (e.g., -D_GNU_SOURCE)
target_compile_options(skfantasy PRIVATE
    ${NCURSES_CFLAGS_OTHER}
    ${GUILE_CFLAGS_OTHER}
)

target_link_directories(skfantasy PRIVATE
    ${NCURSES_LIBRARY_DIRS}
    ${GUILE_LIBRARY_DIRS}
)

# Link libraries
target_link_libraries(skfantasy
    m                     # -lm as in the original Makefile
    ${NCURSES_LIBRARIES}
    ${GUILE_LIBRARIES}
)

# Preprocessor definitions (VERSION with quotes, USE_GUILE)
target_compile_definitions(skfantasy PRIVATE
    VERSION="${VERSION_STRING}"
    USE_GUILE
)

# -------------------------------------------------------------------
#  Create linux_pkg/ and place version.txt + scripts/
# -------------------------------------------------------------------
set(OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/linux_pkg)

# Create the output directory at configure time and write version.txt
file(MAKE_DIRECTORY ${OUTPUT_DIR})
file(WRITE ${OUTPUT_DIR}/version.txt "\"${VERSION_STRING}\"")

# Copy the scripts/ directory after building the executable
add_custom_command(TARGET skfantasy POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/scripts
        ${OUTPUT_DIR}/scripts
    COMMENT "Copying scripts/ to linux_pkg/"
)

# -------------------------------------------------------------------
#  Clean up the whole linux_pkg/ directory on "make clean"
# -------------------------------------------------------------------
set_directory_properties(PROPERTIES ADDITIONAL_CLEAN_FILES ${OUTPUT_DIR})
