# Declare the version of the CMake API for forward-compatibility
cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_STANDARD 11)

project(stabilize)

find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs geometry_msgs message_generation genmsg)

catkin_package()
include_directories(${CMAKE_SOURCE_DIR}/../externals/Navio2/C++/)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${roscpp_INCLUDE_DIRS})
include_directories(include ${catkin_INCLUDE_DIRS})

# Local source files here
SET(TARGET_SRC
    ${CMAKE_SOURCE_DIR}/stabilize/stabHeaders/millis.cpp
    ${CMAKE_SOURCE_DIR}/stabilize/stabHeaders/pid.cpp
)
add_library(stab ${TARGET_SRC})

add_executable(stabilize stabilize.cpp)
target_link_libraries(stabilize navio)
target_link_libraries(stabilize stab)
target_link_libraries(stabilize ${catkin_LIBRARIES})
