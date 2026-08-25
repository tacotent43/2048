cmake_minimum_required(VERSION 3.20)
project(2048_sdl)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.4.10
)
FetchContent_MakeAvailable(SDL3)

FetchContent_Declare(
    SDL3_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG release-3.2.2
)
FetchContent_MakeAvailable(SDL3_ttf)

include_directories(${CMAKE_SOURCE_DIR})

# add_compile_options(-Wall -Wextra -Werror -pedantic -fsanitize=address)
# add_compile_options(-Wall -Wextra -pedantic -fsanitize=address)
add_compile_options(-Wall -pedantic -fsanitize=address)
add_link_options(-fsanitize=address)

add_subdirectory(game)
add_subdirectory(sdl)

add_executable(2048_sdl main.cpp)
target_link_libraries(2048_sdl PRIVATE game sdl SDL3::SDL3 SDL3_ttf::SDL3_ttf)