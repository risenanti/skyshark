# Declare the version of the CMake API for forward-compatibility
cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_STANDARD 11)

project(skySharkMain)

find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg)
catkin_package()


include_directories(include ${catkin_INCLUDE_DIRS})
include_directories(${roscpp_INCLUDE_DIRS})

# Local source files here
SET(TARGET_SRC
    ${CMAKE_SOURCE_DIR}/../Navio2/C++/Navio/RCInput.cpp
    ${CMAKE_SOURCE_DIR}/../Navio2/C++/Navio/Util.cpp
    ${CMAKE_SOURCE_DIR}/../Navio2/C++/Navio/RGBled.cpp   
    ${CMAKE_SOURCE_DIR}/../Navio2/C++/Navio/PWM.cpp
    ${CMAKE_SOURCE_DIR}/../Navio2/C++/Navio/gpio.cpp 
    )
include_directories(${CMAKE_SOURCE_DIR}/../Navio2/C++/)
include_directories(${CMAKE_SOURCE_DIR})

add_library(NAV ${TARGET_SRC})

add_executable(skyshark main.cpp)
target_link_libraries(skyshark NAV)
target_link_libraries(skyshark ${catkin_LIBRARIES})

add_executable(rcSend rcinput/rcinput.cpp)
target_link_libraries(rcSend ${catkin_LIBRARIES})
target_link_libraries(rcSend NAV)
