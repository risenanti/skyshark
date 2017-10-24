cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_STANDARD 11)

project(input_processing)

find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs geometry_msgs message_generation genmsg skyshark_msgs)

generate_messages(
   DEPENDENCIES
   std_msgs
   geometry_msgs
   skyshark_msgs
)

catkin_package()

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${roscpp_INCLUDE_DIRS})
include_directories(include ${catkin_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/../externals/Navio2/C++/)

add_executable(input_processing input_processing.cpp)
target_link_libraries(input_processing navio)
target_link_libraries(input_processing ${catkin_LIBRARIES})
