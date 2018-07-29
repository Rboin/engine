cmake_minimum_required(VERSION 3.1)

project(game)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(INSTALL_CONFIG_DIR "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/cmake")

add_subdirectory(world)
add_subdirectory(render)
add_subdirectory(gui)

include_directories(include)
