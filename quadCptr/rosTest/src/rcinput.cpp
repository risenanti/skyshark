#include <stdio.h>
#include <stdlib.h>

#include "ros/ros.h"
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"

#include "std_msgs/Float32MultiArray.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "rcSend");

  ros::NodeHandle n;

  ros::Publisher pub = n.advertise<std_msgs::Float32MultiArray>("rcSend", 1000);

  ros::Rate loop_rate(10); /*10 HZ*/

  while (ros::ok())
  {

    std_msgs::Float32MultiArray msg;

    msg.data.clear();

	for(int i = 0; i < 4; i++)
	{
		msg.data.push_back(rand()%255);	
	}

    pub.publish(msg);

    ros::spinOnce();
	
	sleep(1);
    //loop_rate.sleep();
  }


  return 0;
}


