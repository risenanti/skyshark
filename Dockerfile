FROM ubuntu:16.04
MAINTAINER Matieu Lagarde <mlaga97@gmail.com>

# Add ROS Sources
RUN echo "deb http://packages.ros.org/ros/ubuntu xenial main" > /etc/apt/sources.list.d/ros-latest.list && \
	apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net:80 --recv-key 421C365BD9FF1F717815A3895523BAEEB01FA116

# Install Packages
RUN apt-get update && apt-get -y install git ros-kinetic-ros-base python-rosinstall python-rosinstall-generator python-wstool build-essential && rm -rf /var/lib/apt/lists/*

# Finish rosdep stuff
RUN rosdep init && rosdep update
