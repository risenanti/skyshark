/*KEITH CONLEY
**USM
**FALL 2018
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "ros/ros.h"
#include "std_msgs/Header.h"
#include "std_msgs/Float32MultiArray.h"
#include "skyshark_msgs/RotorSpeeds.h"

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
	skyshark_msgs::RotorSpeeds sendOutPWM;
	ros::Rate loop_rate(100); /*100 HZ*/
	ros::NodeHandle z;
	ros::Publisher pwmOut = z.advertise<skyshark_msgs::RotorSpeeds>("stabOutput", 1000);
	
	while(1)
	{
		static int i = 0;
		
		sendOutPWM.rotor1 = stabilize.getRCout1();
		sendOutPWM.rotor2 = stabilize.getRCout2();
		sendOutPWM.rotor3 = stabilize.getRCout3();
		sendOutPWM.rotor4 = stabilize.getRCout4();
		
		pwmOut.publish(sendOutPWM);
		ros::spinOnce();	
		loop_rate.sleep();	
		i++;
	}
	
	
	return 0;
}
