#include <stdio.h>
#include <stdlib.h>
#include <time.h>       /* time */

#include "ros/ros.h"
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"

#include "std_msgs/Float32MultiArray.h"

#include "Navio/RCInput.h"
#include "Navio/Util.h"

#define TESTING

float mapRanges(float x, float in_min, float in_max, float out_min, float out_max);
float processCH1(float ch1, std_msgs::Float32MultiArray *msg);

int main(int argc, char **argv)
{
  ros::init(argc, argv, "rcSend");
  ros::NodeHandle n;
  ros::Publisher pub = n.advertise<std_msgs::Float32MultiArray>("rcSend", 1000);
  ros::Rate loop_rate(10); /*10 HZ*/
  
  #ifdef FLYING
  RCInput rcin;

  if(check_apm()) { return 1;}

  rcin.init();
  #endif

  while (ros::ok())
  {

    std_msgs::Float32MultiArray msg;

    msg.data.clear();
    
    #ifdef FLYING
    volatile int rawInput1 = rcin.read(0);
    volatile int rawInput2 = rcin.read(1);
    volatile int rawInput3 = rcin.read(2);
    volatile int rawInput4 = rcin.read(3);
    #endif
    
    #ifdef TESTING
    srand (time(NULL));
    volatile int rawInput1 = rand()%2000+1000;
    volatile int rawInput2 = rand()%2000+1000;
    volatile int rawInput3 = rand()%2000+1000;
    volatile int rawInput4 = rand()%2000+1000;
    #endif

    float dutyCycle =(float)rawInput1/1000;

    if(dutyCycle>1.75) {dutyCycle=1.75;}

    if (dutyCycle<1.0) {dutyCycle=1.0;}

    msg.data.push_back(dutyCycle);

    dutyCycle =(float)rawInput2/1000;
    dutyCycle = processCH1(dutyCycle, &msg);

    msg.data.push_back(dutyCycle);

    pub.publish(msg);

    ros::spinOnce();
	
    loop_rate.sleep();
  }


  return 0;
}


float mapRanges(float x, float in_min, float in_max, float out_min, float out_max)
{
 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//msg[1] == 0 means RIGHT
//msg[1] == 1 means LEFT
float processCH1(float ch1, std_msgs::Float32MultiArray *msg)
{
	float dutyCycle1;
	if(ch1 > 1.55)
	{
	dutyCycle1 = mapRanges(ch1, 1.5, 2, 0, 0.3);
	//printf("\nrc1: = %f R \n", dutyCycle1);
	msg->data.push_back((float) 0.0);

	return dutyCycle1;
	}
	if(ch1 < 1.45) 
	{
	ch1 = 2.5-ch1; //flip slope around to increasing instead of decreasing
	dutyCycle1 = mapRanges(ch1, 1.0, 1.5, 0, 0.3);
	//printf("\nrc1: = %f L \n", dutyCycle1);
	
	msg->data.push_back((float) 1.0);

	return dutyCycle1;
	}
return ch1;
}


