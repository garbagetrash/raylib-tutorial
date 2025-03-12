cmake_minimum_required(VERSION 3.11)
project(raylib-tutorial)

set(CMAKE_C_VERSION 99)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

# Get Raylib 5.5
set(RAYLIB_VERSION 5.5)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES OFF CACHE BOOL "" FORCE) # don't build the supplied games
FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "5.5"
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(raylib)

# Resources path
set(RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)

# Build our examples
add_executable(basic-window src/basic-window.c)
target_link_libraries(basic-window PRIVATE raylib)

add_executable(basic-screen-manager src/basic-screen-manager.c)
target_link_libraries(basic-screen-manager PRIVATE raylib)

add_executable(camera2d src/camera2d.c)
target_link_libraries(camera2d PRIVATE raylib)

add_executable(waving-cubes src/waving-cubes.c)
target_link_libraries(waving-cubes PRIVATE raylib m)

add_executable(heightmap src/heightmap.c)
target_link_libraries(heightmap PRIVATE raylib)
target_compile_definitions(heightmap PRIVATE RESOURCES_DIR="${RESOURCES_DIR}")

add_executable(shaders-raymarching src/shaders-raymarching.c)
target_link_libraries(shaders-raymarching PRIVATE raylib)
target_compile_definitions(shaders-raymarching PRIVATE RESOURCES_DIR="${RESOURCES_DIR}")

add_executable(background-scrolling src/background-scrolling.c)
target_link_libraries(background-scrolling PRIVATE raylib)
target_compile_definitions(background-scrolling PRIVATE RESOURCES_DIR="${RESOURCES_DIR}")
