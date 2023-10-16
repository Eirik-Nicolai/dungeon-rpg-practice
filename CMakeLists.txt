cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

set(CMAKE_CXX_FLAGS "-O0")

set(CXX_STANDARD "C++17")

# add_subdirectory(src)
project(dungeon_game)

set(SRC_MAIN src/main.cpp)

set(SRC_ENGINE
    src/engine/game.cpp
    src/engine/render.cpp
)

set(SRC_UTILS
    src/utils/debug.cpp
    src/utils/globals.cpp
)

set(SRC_SYSTEMS
    src/systems/AI/ai.cpp
    src/systems/input/keypress.cpp
    src/systems/loading/initialize.cpp
    src/systems/logic/logic.cpp
    src/systems/movement/movement.cpp
    src/systems/transition/transition.cpp
)

set(SRC_GAME ${SRC_MAIN} ${SRC_ENGINE} ${SRC_UTILS} ${SRC_SYSTEMS})

message ("Adding executable...")
add_executable(game ${SRC_GAME})

message("Linking dirs....")

target_link_libraries(
    game
    GL
    GLU
    X11
    png
    pthread
    stdc++fs
)

target_include_directories(game
    PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/include"
)
