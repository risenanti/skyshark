# Declare the version of the CMake API for forward-compatibility
cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_STANDARD 11)

project(skySharkMain)

# Local header files here ONLY
#SET(TARGET_H
#    ${CMAKE_SOURCE_DIR}/../Navio2/C++/Navio/RCInput.h
#    ${CMAKE_SOURCE_DIR}/../Navio2/C++/Navio/Util.h
#    ${CMAKE_SOURCE_DIR}/../Navio2/C++/Navio/RGBled.h   
#    ${CMAKE_SOURCE_DIR}/../Navio2/C++/Navio/PWM.h 
#   )

# Local source files here
SET(TARGET_SRC
    ${CMAKE_SOURCE_DIR}/../Navio2/C++/Navio/RCInput.cpp
    ${CMAKE_SOURCE_DIR}/../Navio2/C++/Navio/Util.cpp
    ${CMAKE_SOURCE_DIR}/../Navio2/C++/Navio/RGBled.cpp   
    ${CMAKE_SOURCE_DIR}/../Navio2/C++/Navio/PWM.cpp
    ${CMAKE_SOURCE_DIR}/../Navio2/C++/Navio/gpio.cpp 
    )
include_directories(${CMAKE_SOURCE_DIR}/../Navio2/C++/)

add_library(NAV ${TARGET_SRC})

add_executable(skyshark main.cpp)
target_link_libraries(skyshark NAV)
