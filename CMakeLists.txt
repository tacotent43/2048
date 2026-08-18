cmake_minimum_required(VERSION 3.20)
project(2048_sdl)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.4.10
)
FetchContent_MakeAvailable(SDL3)

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(game)

add_executable(2048_sdl main.cpp)
target_link_libraries(2048_sdl PRIVATE game SDL3::SDL3)