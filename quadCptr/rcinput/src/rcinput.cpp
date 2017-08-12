#include <stdio.h>
#include <stdlib.h>

#include "ros/ros.h"
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"

#include "std_msgs/Float32MultiArray.h"

#include "Navio/RCInput.h"
#include "Navio/Util.h"

#define TESTING

float mapRanges(float x, float in_min, float in_max, float out_min, float out_max);

float boundary(float x);

float processCH(float ch, std_msgs::Float32MultiArray *msg);

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
    volatile int rawInput1 = rand()%2000+1000;
    volatile int rawInput2 = rand()%2000+1000;
    volatile int rawInput3 = rand()%2000+1000;
    volatile int rawInput4 = rand()%2000+1000;
    #endif

    float dutyCycle =(float)rawInput1/1000;

    dutyCycle = boundary(dutyCycle);
    msg.data.push_back(dutyCycle);

    dutyCycle =(float)rawInput2/1000;
    dutyCycle = processCH(dutyCycle, &msg);

    dutyCycle =(float)rawInput3/1000;
    dutyCycle = processCH(dutyCycle, &msg);
    
    dutyCycle =(float)rawInput4/1000;
    dutyCycle = processCH(dutyCycle, &msg);

    pub.publish(msg);

    ros::spinOnce();
	
    loop_rate.sleep();
  }


  return 0;
}

float boundary(float x)
{
	if(x>1.8) {x=1.75;}
	if (x<1.0) {x=1.0;}
	
	return x;
}

float mapRanges(float x, float in_min, float in_max, float out_min, float out_max)
{
 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//msg[1] == 0 means RIGHT
//msg[1] == 1 means LEFT
float processCH(float ch, std_msgs::Float32MultiArray *msg)
{
	float dutyCycle;
	
	if(ch > 1.55)
	{
		dutyCycle = mapRanges(ch, 1.5, 2, 0, 0.3);
		msg->data.push_back((float) 0.0);
		
		msg->data.push_back(dutyCycle);

		return dutyCycle;
	}
	
	
	if(ch < 1.45) 
	{
		ch = 2.5-ch; //flip the value to ascending instead of descending
		dutyCycle = mapRanges(ch, 1.0, 1.5, 0, 0.3);
		
		msg->data.push_back((float) 1.0);
		msg->data.push_back(dutyCycle);

		return dutyCycle;
	}
	
	msg->data.push_back((float) -1.0);
	msg->data.push_back(ch);
	return ch;
}


