#include <stdio.h>
#include <stdlib.h>

#include "ros/ros.h"
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Float32MultiArray.h"

#include "Navio/Util.h"



class receiver
{
	public:
	
	void Callback(const std_msgs::Float32MultiArray::ConstPtr& array);
	private:
	
	float data[7];
};

void receiver::Callback(const std_msgs::Float32MultiArray::ConstPtr& array)
{
	int i = 0;
	for(std::vector<float>::const_iterator it = array->data.begin(); it != array->data.end(); ++it)
	{
		data[i] = *it;
		i++;
	}
	  

return;
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "rcReceiver");


  ros::NodeHandle n;

	receiver rcIN;

  ros::Subscriber sub = n.subscribe("rcSend", 1000, &receiver::Callback, &rcIN);

  ros::spin();

  return 0;
}
