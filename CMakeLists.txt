cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "-g3 -O0 -Wall -Wextra -pedantic")

include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)

message("Fetching FTXUI....")
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui.git
  GIT_TAG v5.0.0
)
FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  message("Populating ftxui...")
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# add_subdirectory(src)
project(dungeon_game)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SRC_MAIN src/main.cpp)

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
    src/systems/rendering/render.cpp
    src/systems/transition/transition.cpp
)

set(SRC_GAME ${SRC_MAIN} ${SRC_UTILS} ${SRC_SYSTEMS})

message ("Adding executable...")
add_executable(game ${SRC_GAME})

message("Linking libraries....")
find_library(ENTT_LIB entt)
target_link_libraries(game
    PRIVATE
    ftxui::component
    ${CURSES_LIBRARIES}
)

target_include_directories(game
    PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/include"
)
