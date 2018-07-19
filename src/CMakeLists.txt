project(game)

add_subdirectory(world)
add_subdirectory(render)
add_subdirectory(gui)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    world
    render
    gui
)
