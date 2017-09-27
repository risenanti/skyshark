# Declare the version of the CMake API for forward-compatibility
cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_STANDARD 11)

project(quadStable)


# Local source files here
SET(TARGET_SRC
    ${CMAKE_SOURCE_DIR}/../../externals/Navio2/C++/Navio/RCInput.cpp
    ${CMAKE_SOURCE_DIR}/../../externals/Navio2/C++/Navio/Util.cpp
    ${CMAKE_SOURCE_DIR}/../../externals/Navio2/C++/Navio/RGBled.cpp   
    ${CMAKE_SOURCE_DIR}/../../externals/Navio2/C++/Navio/PWM.cpp
    ${CMAKE_SOURCE_DIR}/../../externals/Navio2/C++/Navio/gpio.cpp
    ${CMAKE_SOURCE_DIR}/../../externals/Navio2/C++/Navio/MPU9250.cpp 
    ${CMAKE_SOURCE_DIR}/src/millis.cpp
    ${CMAKE_SOURCE_DIR}/src/pid.cpp
    )
include_directories(${CMAKE_SOURCE_DIR}/../../externals/Navio2/C++/)
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR})

add_library(NAV ${TARGET_SRC})

add_executable(quadStable src/main.cpp)
target_link_libraries(quadStable NAV)

