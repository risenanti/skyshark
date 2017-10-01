# Declare the version of the CMake API for forward-compatibility
cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_STANDARD 11)

project(pwmOutput)

find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs geometry_msgs message_generation genmsg)

catkin_package()
include_directories(${CMAKE_SOURCE_DIR}/../externals/Navio2/C++/)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${roscpp_INCLUDE_DIRS})
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(pwmOutput pwmOutput.cpp)
target_link_libraries(pwmOutput navio)
target_link_libraries(pwmOutput ${catkin_LIBRARIES})
