cmake_minimum_required(VERSION 3.10)
project(raylib-tutorial)

set(CMAKE_C_VERSION 99)
add_compile_options(-fsanitize=address -fno-omit-frame-pointer -Wall -Werror)
add_link_options(-fsanitize=address)

set(RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)

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
