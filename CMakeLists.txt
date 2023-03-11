cmake_minimum_required(VERSION 3.18)
project(pong C)

include(src/generated/CMakeLists.txt)

set(GBDKDIR "/opt/gbdk/")

if (DEFINED ENV{GBDKDIR})
    set(GBDKDIR $ENV{GBDKDIR})
endif()

if (NOT ${CMAKE_C_COMPILER})
    set(CMAKE_C_COMPILER "lcc")
endif ()

include_directories(${GBDKDIR}include)
include_directories(${PROJECT_SOURCE_DIR}/src)

#SET(CMAKE_EXE_LINKER_FLAGS  "-Wm-yC")

add_executable(pong.gb
        src/main.c
        src/sprite.c
        src/render.c
        src/input.c
        src/sound.c
        src/states/states_type.c
        src/states/state_gameplay.c
        src/states/state_screen_start.c
        src/states/state_game-over.c
        ${GENERATE_SRC}
        )
