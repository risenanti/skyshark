/*KEITH CONLEY
**USM
**FALL 2018
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "ros/ros.h"

#include "std_msgs/Float32MultiArray.h"
#include "geometry_msgs/Vector3.h"
#include "skyshark_msgs/VelocityTarget.h"

#include "stabHeaders/pid.h"
#include "stabHeaders/millis.h"
#include "stabHeaders/rcDef.h"

void chatterCallback(const skyshark_msgs::VelocityTarget &message)
{
	ROS_INFO("I heard: [%d]", message.velocity.z);
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "stabilizePID");
	
	ros::NodeHandle n;
	
	ros::Subscriber sub = n.subscribe("velocityTarget", 1000, chatterCallback);
	
	while(1)
	{
		ros::spin();		
	}
	
	
	return 0;
}
