project(World VERSION 0.0.1 DESCRIPTION "World library")

#add_subdirectory(${PROJECT_INCLUDE_DIR})

find_package(glm REQUIRED)

set(SOURCE_FILES
    include/world.hpp
    include/entity.h src/entity.cpp
    include/movingentity.h src/movingentity.cpp
    include/axis.h src/axis.cpp
)

add_library(world SHARED ${SOURCE_FILES})
target_include_directories(world PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_executable(world_bin "main.cpp")
target_link_libraries(world_bin PRIVATE world)

install(TARGETS world
    LIBRARY DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/world
    ARCHIVE DESTINATION ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/world)
