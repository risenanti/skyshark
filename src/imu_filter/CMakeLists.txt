#Copyright Jackal Robotics###############################################
#Keith Conley 2017        ###############################################

cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_STANDARD 11)

project(imu_filter)

find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs geometry_msgs message_generation genmsg skyshark_msgs)

generate_messages(
   DEPENDENCIES
   std_msgs
   geometry_msgs
   skyshark_msgs
)

catkin_package()
include_directories(${CMAKE_SOURCE_DIR}/../externals/Navio2/C++/)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${roscpp_INCLUDE_DIRS})
include_directories(include ${catkin_INCLUDE_DIRS})

# Local source files here
#SET(TARGET_SRC
#    ${CMAKE_SOURCE_DIR}/stabilize/stabHeaders/millis.cpp
#    ${CMAKE_SOURCE_DIR}/stabilize/stabHeaders/pid.cpp
#${CMAKE_SOURCE_DIR}/stabilize/stabHeaders/stabClass.cpp
#)
#add_library(stabil ${TARGET_SRC})

add_executable(imu_filter complimentaryFilter.cpp)
target_link_libraries(imu_filter navio)
#target_link_libraries(stabilize stabil)
target_link_libraries(imu_filter ${catkin_LIBRARIES})
add_dependencies(imu_filter ${catkin_EXPORTED_TARGETS})

#Copyright Jackal Robotics###############################################
#Keith Conley 2017        ###############################################
