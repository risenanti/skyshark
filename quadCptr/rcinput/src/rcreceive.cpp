#include <stdio.h>
#include <stdlib.h>

#include "ros/ros.h"
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Float32MultiArray.h"

#include "Navio/Util.h"

float Arr[4];

void chatterCallback(const std_msgs::Float32MultiArray::ConstPtr& array)
{
    int i = 0;
	for(std::vector<float>::const_iterator it = array->data.begin(); it != array->data.end(); ++it)
	{
		Arr[i] = *it;
		i++;
	}
	  
	  for(int j = 0; j < 3; j++)
	{
		printf("%f, ", Arr[j]);
	}
	printf("\n");

return;
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "rcReceiver");


  ros::NodeHandle n;


  ros::Subscriber sub = n.subscribe("rcSend", 1000, chatterCallback);

  ros::spin();

  return 0;
}
