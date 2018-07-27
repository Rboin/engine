project(World VERSION 0.0.1 DESCRIPTION "World library")

#add_subdirectory(${PROJECT_INCLUDE_DIR})

find_package(glm REQUIRED)

set(SOURCE_FILES
    src/entity.cpp
    src/movingentity.cpp
    src/axis.cpp
)

add_library(world SHARED ${SOURCE_FILES})
target_include_directories(world PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_executable(world_bin "main.cpp")
target_link_libraries(world_bin PRIVATE world)
