#Copyright Jackal Robotics###############################################
#Keith Conley 2017        ###############################################

cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_STANDARD 11)

project(sensors)

find_package(catkin REQUIRED COMPONENTS rospy std_msgs sensor_msgs message_generation genmsg)

generate_messages(
   DEPENDENCIES
   std_msgs
   sensor_msgs
)

catkin_package()

#Copyright Jackal Robotics###############################################
#Keith Conley 2017        ###############################################
