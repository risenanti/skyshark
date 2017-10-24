// System headers
#include <iostream>

// ROS headers
#include "ros/ros.h"

// Message headers
#include "geometry_msgs/Vector3.h"
#include "skyshark_msgs/VelocityTarget.h"
#include "skyshark_msgs/StabTargets.h"
 
#define RC_THR_MIN   1.070
#define RC_YAW_MIN   1.068
#define RC_YAW_MAX   1.915
#define RC_PIT_MIN   1.077
#define RC_PIT_MAX   1.915
#define RC_ROL_MIN   1.090
#define RC_ROL_MAX   1.913

float map(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

double constrain(double x, double a, double b) 
{
    if(x < a) {
        return a;
    }
    else if(b < x) {
        return b;
    }
    else
        return x;
}
 
 skyshark_msgs::StabTargets targets;
 
 void rcCallback(const skyshark_msgs::VelocityTarget &message)
 {
	float rcThrottle = message.velocity.z;
	float rcPitch = message.velocity.x;
	float rcRoll = message.velocity.y;
	float rcYaw = message.yaw;
	
	targets.rollTarget = map(rcRoll, RC_ROL_MIN, RC_ROL_MAX, -45, 45);
	targets.pitchTarget = map(rcPitch, RC_PIT_MIN, RC_PIT_MAX, -45, 45);
	targets.yawTarget= map(rcYaw, RC_YAW_MIN, RC_YAW_MAX, -180, 180);
	targets.throttleMag = rcThrottle;
 }

int main(int argc, char **argv) {
	// ROS stuff
	ros::init(argc, argv, "rcinputRaw");
	ros::NodeHandle n, s;
	ros::Rate loop_rate(500);
	
	ros::Subscriber sub  = n.subscribe("velocityTarget", 1000, rcCallback);
	
	ros::Publisher frameAngleOut = s.advertise<skyshark_msgs::StabTargets>("stabTarget",1000);

	while(ros::ok()) 
	{	
		// Other ROS maintenance things
		ros::spinOnce();
		frameAngleOut.publish(targets);
		loop_rate.sleep();
	}

	return 0;
}


