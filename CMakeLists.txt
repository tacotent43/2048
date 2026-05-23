cmake_minimum_required(VERSION 3.25.1)
project(game)

include(FetchContent)

FetchContent_Declare(SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 3.0.x)
FetchContent_MakeAvailable(SFML)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Werror -pedantic -fsanitize=address")
# set(CMAKE_CXX_FLAGS "-g -Wall -pedantic")

file(GLOB SRC source/*.cpp)
# file(GLOB THIRD thirdpart/*.hpp)

add_executable(game 
  ${SRC}
#   ${THIRD}
  main.cpp
)

include_directories(
  ./include/
#   ./thirdpart/
)

target_link_libraries(game PRIVATE 
  sfml-graphics
)