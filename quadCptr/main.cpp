#include <unistd.h>
#include <stdio.h>
#include "flightModel.hpp"



int main(int argc, char **argv)
{
  ros::init(argc, argv, "mainLoop");

  ros::NodeHandle n;

  flightModel Drive;

  ros::Subscriber sub = n.subscribe("rcSend", 1000, &flightModel::rcCallback, &Drive);


	while(true)
	{
		Drive.processControlInput();
	}
	return 1;
}
