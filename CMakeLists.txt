cmake_minimum_required(VERSION 3.11)
project(raylib-tutorial)

set(CMAKE_C_VERSION 99)

# Get Raylib 5.5
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
  endif()
endif()

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
