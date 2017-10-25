#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "ros/ros.h"
#include "skyshark_msgs/VelocityTarget.h"
#include "skyshark_msgs/frameAngle.h" //angle of frame body
#include "skyshark_msgs/StabTargets.h"//targets from rcInput

#include "pid.h"
#include "millis.h"
#include "rcDef.h"

#include "stabClass.h"


stabClass::stabClass()
{
	createMillisTimer();	
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

void stabClass::input_processingCallback(const skyshark_msgs::StabTargets &message)
{
	rcthr  = message.throttleMag;
	rcyaw  = message.yawTarget;
	rcpit  = message.pitchTarget;
	rcroll = message.rollTarget;
}

void stabClass::frame_angleCallback(const skyshark_msgs::frameAngle &message)
{
	roll = message.rollAngle;
	pitch = message.pitchAngle;
	yaw = message.yawAngle;
}

/*Compute the stab values loop*/
void stabClass::computeStab(void)
{
	yaw_target = 0; 
	
	if(rcthr > RC_THR_MIN + 0.100) 
	{  // Throttle raised, turn on stablisation.
		float pitch_stab_output = constrain(pitchStab.getPID((float)rcpit - pitch), -0.250, 0.250); 
		float roll_stab_output = constrain(rollStab.getPID((float)rcroll - roll), -0.250, 0.250);
		float yaw_stab_output = constrain(yawStab.getPID(wrap_180(yaw_target - yaw)), -0.360, 0.360);

		//if pilot asking for yaw change feed directly to rate pid (overwriting yaw stab output)
		//side note: cheating PID

		if(abs(rcyaw ) > 5) {
		  yaw_stab_output = rcyaw;
		  yaw_target = yaw;   // remember this yaw for when pilot stops
		}

		// rate PIDS
		long pitch_output =  (long) constrain(pitchRate.getPID(pitch_stab_output - pitch), -0.500, 0.500);  
		long roll_output =   (long) constrain(rollRate.getPID(roll_stab_output - roll), -0.500, 0.500);  
		long yaw_output =    (long) constrain(yawRate.getPID(yaw_stab_output - yaw), -0.500, 0.500);  

		rcOut1 = (rcthr + roll_output + pitch_output - yaw_output);
		rcOut2 = (rcthr + roll_output - pitch_output + yaw_output);
		rcOut3 = (rcthr - roll_output + pitch_output + yaw_output);
		rcOut4 = (rcthr - roll_output - pitch_output - yaw_output);
		}

		else {
			rcOut1 = RC_THR_MIN; 
			rcOut2 = RC_THR_MIN;
			rcOut3 = RC_THR_MIN;
			rcOut4 = RC_THR_MIN;
			yaw_target = yaw;
			pitchRate.resetI();
			yawRate.resetI();
			rollRate.resetI();
		}
}

float stabClass::getRCout1()
{
	return rcOut1;
}
float stabClass::getRCout2()
{
	return rcOut2;
}
float stabClass::getRCout3()
{
	return rcOut3;
}
float stabClass::getRCout4()
{
	return rcOut4;
}
