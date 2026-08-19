file(
    GLOB_RECURSE SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp
)

add_library(
    sdl STATIC 
    ${SOURCES}
)

target_link_libraries(
    sdl PUBLIC 
    SDL3::SDL3
)

target_include_directories(
    sdl PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)