#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "ros/ros.h"

#include "std_msgs/Header.h"
#include "sensor_msgs/Imu.h"

class complimentaryFilter
{
	
};

int main(int argc, char **argv)
{
	ros::init(argc, argv, "imu_filter");
	
	ros::NodeHandle n;
	ros::Rate loop_rate(500); /*500 HZ*/
	ros::Subscriber nSub = n.subscribe("mpuRaw", 1000, &stabClass::mpuCallback, &stabilize);
	
	while(1)
	{
		ros::spinOnce();	
		loop_rate.sleep();	
	}
	
	return 0;
}
