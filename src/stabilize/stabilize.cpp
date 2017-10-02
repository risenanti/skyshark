/*KEITH CONLEY
**USM
**FALL 2018
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "ros/ros.h"

#include "stabHeaders/stabClass.h"


int main(int argc, char **argv)
{
	/*ROS INITIALIZATION*/
	stabClass stabilize;
	ros::init(argc, argv, "stabilizePID");
	ros::NodeHandle n,s;
	ros::Subscriber sub  = n.subscribe("velocityTarget", 1000, &stabClass::rcCallback, &stabilize);
	ros::Subscriber nSub = s.subscribe("mpuRaw", 1000, &stabClass::mpuCallback, &stabilize);
	
	while(1)
	{
		ros::spin();
				
	}
	
	
	return 0;
}
