cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_STANDARD 11)

project(skyshark_msgs)

find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs geometry_msgs message_generation genmsg)

add_message_files(
  FILES
  VelocityTarget.msg
  Velocity.msg
  Position.msg
  Acceleration.msg
  RotorSpeeds.msg
  frameAngle.msg
)

generate_messages(
   DEPENDENCIES
   std_msgs
   geometry_msgs
)

catkin_package()
