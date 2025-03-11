cmake_minimum_required(VERSION 3.10)
project(raylib-tutorial)

set(CMAKE_C_VERSION 99)
add_compile_options(-fsanitize=address -fno-omit-frame-pointer -Wall -Werror)
add_link_options(-fsanitize=address)

add_executable(basic-window src/basic-window.c)
target_link_libraries(basic-window PRIVATE raylib)

add_executable(basic-screen-manager src/basic-screen-manager.c)
target_link_libraries(basic-screen-manager PRIVATE raylib)
