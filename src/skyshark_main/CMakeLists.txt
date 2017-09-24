# Declare the version of the CMake API for forward-compatibility
cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_STANDARD 11)

project(skyshark_main)

find_package(catkin REQUIRED COMPONENTS message_generation roscpp rospy std_msgs genmsg roscpp rospy std_msgs message_generation genmsg)

generate_messages(
   DEPENDENCIES
   std_msgs
)

catkin_package(
  CATKIN_DEPENDS
  message_runtime
)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${roscpp_INCLUDE_DIRS})
include_directories(include ${catkin_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/../externals/Navio2/C++/)

add_executable(skyshark main.cpp)
target_link_libraries(skyshark navio)
target_link_libraries(skyshark ${catkin_LIBRARIES})

add_executable(rcSend rcinput/rcinput.cpp)
target_link_libraries(rcSend ${catkin_LIBRARIES})
target_link_libraries(rcSend navio)
