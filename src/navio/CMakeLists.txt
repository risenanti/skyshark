# Declare the version of the CMake API for forward-compatibility
cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_STANDARD 11)

project(navio)

find_package(catkin REQUIRED COMPONENTS)

catkin_package(
  CATKIN_DEPENDS
)

# Local source files here
SET(TARGET_SRC
    ${CMAKE_SOURCE_DIR}/../externals/Navio2/C++/Navio/RCInput.cpp
    ${CMAKE_SOURCE_DIR}/../externals/Navio2/C++/Navio/Util.cpp
    ${CMAKE_SOURCE_DIR}/../externals/Navio2/C++/Navio/RGBled.cpp   
    ${CMAKE_SOURCE_DIR}/../externals/Navio2/C++/Navio/PWM.cpp
    ${CMAKE_SOURCE_DIR}/../externals/Navio2/C++/Navio/gpio.cpp 
)

include_directories(${CMAKE_SOURCE_DIR}/../externals/Navio2/C++/)

add_library(navio ${TARGET_SRC})
