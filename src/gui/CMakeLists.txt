project(game_gui)
set(CMAKE_CXX_STANDARD 14)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_definitions(
    ${OPENGL_DEFINITIONS}
    ${QT_DEFINITIONS}
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)



find_library(world REQUIRED)
find_library(render REQUIRED)

include_directories(
    ${CMAKE_INCLUDE_CURRENT_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${OPENGL_INCLUDE_DIRS}
    ../world
    ../render
)

set(SOURCES
    openglwindow.h openglwindow.cpp
    qtopenglproxy.h qtopenglproxy.cpp
    resources.qrc
)

add_library(gui SHARED ${SOURCES})
target_link_libraries(gui ${OPENGL_LIBRARIES} Qt5::Core Qt5::Widgets ${OPENGL_LIBRARIES} world render)

add_executable(gui_bin "main.cpp")
target_link_libraries(gui_bin gui)
