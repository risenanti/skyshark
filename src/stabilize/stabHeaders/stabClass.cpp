#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "ros/ros.h"
#include "std_msgs/Float32MultiArray.h"
#include "geometry_msgs/Vector3.h"
#include "skyshark_msgs/VelocityTarget.h"

#include "std_msgs/Header.h"
#include "sensor_msgs/Imu.h"

#include "pid.h"
#include "millis.h"
#include "rcDef.h"

#include "stabClass.h"


void stabClass::rcCallback(const skyshark_msgs::VelocityTarget &message)
{
	rcZ = message.velocity.z;
	rcX = message.velocity.x;
	rcY = message.velocity.y;
	rcYaw = message.yaw;
}

void stabClass::mpuCallback(const sensor_msgs::Imu &message)
{
	gyroX = message.angular_velocity.x;
	gyroY = message.angular_velocity.y;
	gyroZ = message.angular_velocity.z;
	
	/*computing stabilization loop*/
	computeStab();
}

stabClass::stabClass()
{
	/*SETUP PIDS*/
	pitchRate.SetTunings(0.70, 1.00, 0.00);
	pitchRate.setImax(50.00);
	
	rollRate.SetTunings(0.700, 1.00, 0.00);
	rollRate.setImax(50);
	
	yawRate.SetTunings(2.70, 1.00, 0.00);
	yawRate.setImax(50.00);
	
	yawStab.SetTunings(10.00, 0.00, 0.00);
	
	yaw_target = 0;
}

void stabClass::mapRCval(void)
{
	rcthr = rcZ;
	rcyaw = map(rcYaw, RC_YAW_MIN, RC_YAW_MAX, -180, 180);
	rcpit = map(rcX, RC_PIT_MIN, RC_PIT_MAX, -45, 45);
	rcroll = map(rcY, RC_ROL_MIN, RC_ROL_MAX, -45, 45);
}

void stabClass::setStabVal(void)
{
	roll  = gyroX*(double)180/M_PI; //measured values inputs to PID converted from radians to degrees
	pitch = gyroY*(double)180/M_PI;
	yaw   = gyroZ*(double)180/M_PI; 
}

/*Compute the stab values loop*/
void stabClass::computeStab(void)
{
	yaw_target = 0; 
	mapRCval();
	setStabVal();	
	
	if(rcthr > RC_THR_MIN + 100) 
	{  // Throttle raised, turn on stablisation.
		float pitch_stab_output = constrain(pitchStab.getPID((float)rcpit - pitch), -250, 250); 
		float roll_stab_output = constrain(rollStab.getPID((float)rcroll - roll), -250, 250);
		float yaw_stab_output = constrain(yawStab.getPID(wrap_180(yaw_target - yaw)), -360, 360);

		//if pilot asking for yaw change feed directly to rate pid (overwriting yaw stab output)
		//side note: cheating PID

		if(abs(rcyaw ) > 5) {
		  yaw_stab_output = rcyaw;
		  yaw_target = yaw;   // remember this yaw for when pilot stops
		}

		// rate PIDS
		long pitch_output =  (long) constrain(pitchRate.getPID(pitch_stab_output - pitch), - 500, 500);  
		long roll_output =   (long) constrain(rollRate.getPID(roll_stab_output - roll), -500, 500);  
		long yaw_output =    (long) constrain(yawRate.getPID(yaw_stab_output - yaw), -500, 500);  

		rcOut1 = (rcthr + roll_output + pitch_output - yaw_output)/1000;
		rcOut2 = (rcthr + roll_output - pitch_output + yaw_output)/1000;
		rcOut3 = (rcthr - roll_output + pitch_output + yaw_output)/1000;
		rcOut4 = (rcthr - roll_output - pitch_output - yaw_output)/1000;
		}

		else {
			rcOut1 = 1.000; 
			rcOut2 = 1.000;
			rcOut3 = 1.000;
			rcOut4 = 1.000;
			yaw_target = yaw;
			pitchRate.resetI();
			yawRate.resetI();
			rollRate.resetI();
		}
}
