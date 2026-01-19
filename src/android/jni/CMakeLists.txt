cmake_minimum_required(VERSION 3.10)

project(skfantasy C)

# Build shared library
add_library(skfantasy SHARED
    game.c
    render.c
    chain.c
    surface.c
    memory.c
    android-main.c
    model.c
)

# Compiler flags
target_compile_options(skfantasy PRIVATE
    -Wall
    -Wextra
    -fPIC
    -DSK_IS_ANDROID
)

target_link_libraries(skfantasy
    android
    log
    m)
