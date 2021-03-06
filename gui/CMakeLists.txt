project(game_gui)
set(CMAKE_CXX_STANDARD 14)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

if (Qt5_FOUND)
    if (Qt5_VERSION VERSION_LESS 5.11.1)
        message(FATAL_ERROR "Could not find supported Qt5 version (>= 5.8)")
    endif()
endif(Qt5_FOUND)

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
)

set(SOURCES
    openglwindow.h openglwindow.cpp
    qtopenglproxy.hpp
    resources.qrc
)

add_library(gui SHARED ${SOURCES})
target_link_libraries(gui ${OPENGL_LIBRARIES} Qt5::Core Qt5::Widgets ${OPENGL_LIBRARIES} world render)

add_executable(gui_bin "main.cpp")
target_link_libraries(gui_bin gui)
