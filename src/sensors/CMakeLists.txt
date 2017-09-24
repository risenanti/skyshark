cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_STANDARD 11)

project(sensors)

find_package(catkin REQUIRED COMPONENTS rospy std_msgs sensor_msgs message_generation genmsg)

add_message_files(
  FILES
)

generate_messages(
   DEPENDENCIES
   std_msgs
   sensor_msgs
)

catkin_package()
