project(game_render)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)

add_definitions(${OPENGL_DEFINITIONS})

set(PUBLIC_HEADERS
    include/camera.hpp
    include/openglfunctionproxy.h
    include/renderer.h
    include/renderableentity.h
    include/playableentity.h
    include/mesh.h
    include/material.h
    include/shader.h
    include/shaderinformation.h
    include/vertex.h
    include/texture.h
    include/renderobject.h
    include/fpscamera.h
    include/lightrenderobject.h
    include/rendercomponent.h)


set(SOURCE_FILES
    src/renderer/renderer.cpp
    src/renderer/renderobject.cpp
    src/renderer/vertex.cpp
    src/renderer/texture.cpp
    src/renderer/mesh.cpp
    src/renderer/material.cpp
    src/shader/shader.cpp
    src/shader/shaderinformation.cpp
    src/camera/fpscamera.cpp
    src/entities/renderableentity.cpp
    src/entities/playableentity.cpp
    src/renderer/lightrenderobject.cpp
    src/renderer/rendercomponent.cpp
    )

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${RENDER_INCLUDE_DIR}
    include
)

find_library(world REQUIRED)

add_library(render SHARED ${PUBLIC_HEADERS} ${SOURCE_FILES})
target_include_directories(render PUBLIC include)
target_link_libraries(render ${OPENGL_LIBRARIES} glm world)

add_executable(render_bin "main.cpp")
target_link_libraries(render_bin PRIVATE render)

install(TARGETS render
    LIBRARY DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/render
    ARCHIVE DESTINATION ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/render)
