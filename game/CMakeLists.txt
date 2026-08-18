file(
    GLOB_RECURSE SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp
)

add_library(
    game STATIC 
    ${SOURCES}
)

target_include_directories(
    game PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)