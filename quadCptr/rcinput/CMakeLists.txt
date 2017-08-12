cmake_minimum_required(VERSION 2.8.3)

set (CMAKE_CXX_STANDARD 11)

project(rcSender)

find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg)
catkin_package()


include_directories(include ${catkin_INCLUDE_DIRS})
include_directories(${roscpp_INCLUDE_DIRS})


SET(TARGET_SRC
    ${CMAKE_SOURCE_DIR}/../../Navio2/C++/Navio/RCInput.cpp
    ${CMAKE_SOURCE_DIR}/../../Navio2/C++/Navio/Util.cpp
    ${CMAKE_SOURCE_DIR}/../../Navio2/C++/Navio/RGBled.cpp   
    ${CMAKE_SOURCE_DIR}/../../Navio2/C++/Navio/PWM.cpp
    ${CMAKE_SOURCE_DIR}/../../Navio2/C++/Navio/gpio.cpp 
    )
include_directories(${CMAKE_SOURCE_DIR}/../../Navio2/C++/)

add_library(NAV ${TARGET_SRC})

add_executable(rcSend src/rcinput.cpp)
target_link_libraries(rcSend ${catkin_LIBRARIES})
target_link_libraries(rcSend NAV)

add_executable(rcReceive src/rcreceive.cpp)
target_link_libraries(rcReceive ${catkin_LIBRARIES})
target_link_libraries(rcReceive NAV)
