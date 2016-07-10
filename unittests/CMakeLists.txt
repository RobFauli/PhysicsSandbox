#cmake_minimum_required(VERSION 3.2.2)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project(tests)

add_subdirectory(lib/googletest)
add_subdirectory(tests)