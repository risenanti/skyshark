cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_STANDARD 11)

project(rcinput)

find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs geometry_msgs message_generation genmsg skyshark_msgs)

generate_messages(
   DEPENDENCIES
   std_msgs
   geometry_msgs
   skyshark_msgs
)

catkin_package(CATKIN_DEPENDS message_runtime std_msgs geometry_msgs skyshark_msgs)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${roscpp_INCLUDE_DIRS})
include_directories(include ${catkin_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/../externals/Navio2/C++/)

add_executable(rcinput rcinput.cpp)
target_link_libraries(rcinput navio)
target_link_libraries(rcinput ${catkin_LIBRARIES})
add_dependencies(rcinput ${catkin_EXPORTED_TARGETS})
