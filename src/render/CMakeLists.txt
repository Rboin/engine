project(game_render)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)

add_definitions(${OPENGL_DEFINITIONS})

set(RENDERERS
    renderer/renderer.h renderer/renderer.cpp
    renderer/renderobject.h renderer/renderobject.cpp
    renderer/vertex.h renderer/vertex.cpp
    renderer/texture.h renderer/texture.cpp
    renderer/mesh.h renderer/mesh.cpp
    renderer/material.h renderer/material.cpp
    renderer/openglfunctionproxy.h
)

set(SHADERS
    shader/shader.h shader/shader.cpp
    shader/shaderinformation.h shader/shaderinformation.cpp
)

set(ENTITIES
    camera/camera.h camera/camera.cpp
    entities/renderableentity.h entities/renderableentity.cpp
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(
    ${CMAKE_INCLUDE_CURRENT_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${OPENGL_INCLUDE_DIRS}
    ../world
)



add_library(render SHARED ${RENDERERS} ${SHADERS} ${ENTITIES})
target_link_libraries(render glm ${OPENGL_LIBRARIES} world)

add_executable(render_bin "main.cpp")
target_link_libraries(render_bin render)
