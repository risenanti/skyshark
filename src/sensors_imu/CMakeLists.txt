#Copyright Jackal Robotics###############################################
#Keith Conley 2017        ###############################################

cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_STANDARD 11)

project(sensors_imu)

find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs message_generation genmsg geometry_msgs)

generate_messages(
   DEPENDENCIES
   geometry_msgs
)

catkin_package()

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${roscpp_INCLUDE_DIRS})
include_directories(include ${catkin_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/../externals/Navio2/C++/)

add_executable(imu imu.cpp)
target_link_libraries(imu navio)
target_link_libraries(imu ${catkin_LIBRARIES})

#Copyright Jackal Robotics###############################################
#Keith Conley 2017        ###############################################
