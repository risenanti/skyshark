# %Tag(FULLTEXT)%
cmake_minimum_required(VERSION 2.8.3)
project(rcSender)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg)



## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})
# Add the headers from roscpp
include_directories(${roscpp_INCLUDE_DIRS})

add_executable(rcSend src/rcinput.cpp)
target_link_libraries(rcSend ${catkin_LIBRARIES})


add_executable(listener src/listener.cpp)
target_link_libraries(listener ${catkin_LIBRARIES})

