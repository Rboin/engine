project(game_world)

find_package(glm REQUIRED)

set(SOURCE_FILES
    entity.h entity.cpp
    movingentity.h movingentity.cpp
    world.hpp
)

include_directories(${CMAKE_INCLUDE_CURRENT_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(world SHARED ${SOURCE_FILES})
target_link_libraries(world glm)

add_executable(world_bin "main.cpp")
target_link_libraries(world_bin world)
