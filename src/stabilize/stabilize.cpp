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

#include "stabHeaders/stabClass.h"


int main(int argc, char **argv)
{
	/*ROS INITIALIZATION*/
	stabClass stabilize;
	ros::init(argc, argv, "stabilizePID");
	ros::NodeHandle n,s;
	ros::Subscriber sub  = n.subscribe("velocityTarget", 1000, &stabClass::rcCallback, &stabilize);
	ros::Subscriber nSub = s.subscribe("mpuRaw", 1000, &stabClass::mpuCallback, &stabilize);
	
	/*publisher setup*/
	std_msgs::Float32MultiArray sendOutPWM;
	ros::Rate loop_rate(100); /*100 HZ*/
	ros::NodeHandle z;
	ros::Publisher pwmOut = z.advertise<std_msgs::Float32MultiArray>("stabOutput", 1000);
	
	while(1)
	{
		sendOutPWM.data.clear();
		sendOutPWM.data.push_back(stabilize.getRCout1());
		sendOutPWM.data.push_back(stabilize.getRCout2());
		sendOutPWM.data.push_back(stabilize.getRCout3());
		sendOutPWM.data.push_back(stabilize.getRCout4());
		
		pwmOut.publish(sendOutPWM);
		ros::spin();	
		loop_rate.sleep();	
	}
	
	
	return 0;
}
