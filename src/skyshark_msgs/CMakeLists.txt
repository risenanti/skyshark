cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_STANDARD 11)

project(skyshark_msgs)

find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs geometry_msgs message_generation genmsg)

add_message_files(
  DIRECTORY msg
  FILES
  VelocityTarget.msg
  Velocity.msg
  Position.msg
  Acceleration.msg
  RotorSpeeds.msg
  frameAngle.msg
  StabTargets.msg
)

generate_messages(
   DEPENDENCIES
   std_msgs
   geometry_msgs
)

catkin_package(CATKIN_DEPENDS message_runtime std_msgs geometry_msgs)

include_directories(
  ${catkin_INCLUDE_DIRS}
)
