#include <stdio.h>
#include <stdlib.h>
#include "ros/ros.h"

/*add rcinput struct*/
#include "rcinput/rcinputContainer.h"

/*Navio Drivers*/
#include "Navio/RCInput.h"
#include "Navio/Util.h"

#define FLYING

int main(int argc, char **argv)
{
  ros::init(argc, argv, "rcinputRaw");
  ros::NodeHandle n;
  ros::Publisher pub = n.advertise<rcinput::rcinputContainer>("rcinputRaw", 1000);
  ros::Rate loop_rate(10); /*10 HZ*/
  
	  #ifdef FLYING
	  RCInput rcin;

	  if(check_apm()) { return 1;}

	  rcin.init();
	  #endif

  while (ros::ok())
  {

    rcinput::rcinputContainer msg;


    #ifdef FLYING
    /*array element 0 left stick up and down*/
    volatile int rawInput1 = rcin.read(0);
    
    /*Array element 1 is direction and 2 is magnitude Right stick Side to Side */
    volatile int rawInput2 = rcin.read(1);
    
    /*Array Element 3 is direction and 4 is magnitude Right Stick Up and Down*/
    volatile int rawInput3 = rcin.read(2);
    
    /*Array Element 5 is direction and 6 is magnitude Left Stick Side to Side*/
    volatile int rawInput4 = rcin.read(3);
    #endif
    
		#ifdef TESTING
		msg.input1 = rand()%2000+1000;
		msg.input2 = rand()%2000+1000;
		msg.input3 = rand()%2000+1000;
		msg.input4 = rand()%2000+1000;
		#endif

    pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }


  return 0;
}


