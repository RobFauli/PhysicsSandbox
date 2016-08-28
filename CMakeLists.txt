cmake_minimum_required(VERSION 3.2.2)
project(PhysicsSandbox)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -ansi -pedantic")
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)

add_executable(physics_sandbox ${SOURCE_FILES})

include_directories(Physics Visualization)

add_subdirectory(Physics)
add_subdirectory(Visualization)
add_subdirectory(Application)
add_subdirectory(unittests)


target_link_libraries(physics_sandbox viphy physics visualization)
