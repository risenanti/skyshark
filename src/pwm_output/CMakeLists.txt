cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_STANDARD 11)

project(pwm_output)

find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs message_generation genmsg skyshark_msgs)

catkin_package()
include_directories(${CMAKE_SOURCE_DIR}/../externals/Navio2/C++/)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${roscpp_INCLUDE_DIRS})
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(pwm_output pwm_output.cpp)
target_link_libraries(pwm_output navio)
target_link_libraries(pwm_output ${catkin_LIBRARIES})

