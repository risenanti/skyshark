# Declare the version of the CMake API for forward-compatibility
cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_STANDARD 11)

project(timmer)

include_directories(${CMAKE_SOURCE_DIR})


add_executable(timtest main.cpp)

