#ifndef stabClass_h
#define stabClass_h

#include "std_msgs/Header.h"
#include "skyshark_msgs/VelocityTarget.h"
#include "skyshark_msgs/frameAngle.h" //angle of frame body
#include "skyshark_msgs/StabTargets.h"//targets from rcInput
#include "pid.h"
#include "ros/ros.h"

class stabClass
{
	public:
	
	void input_processingCallback(const skyshark_msgs::StabTargets &message);
	void frame_angleCallback(const skyshark_msgs::frameAngle &message);
	
	void computeStab(void);
	float getRCout1();
	float getRCout2();
	float getRCout3();
	float getRCout4();
	
	stabClass();
	
	private:
	double rcthr, rcyaw, rcpit, rcroll;	
	double roll; //measured values inputs to PID
	double pitch;
	double yaw; 
		
	double yaw_target;
	
	/*velocity Outputs DO NOT LEAVE FIX THIS SHIT*/
	float rcOut1, rcOut2, rcOut3, rcOut4;
	
	/*Create Rate PIDS*/
	PID pitchRate;
	PID rollRate;
	PID yawRate;
	
	/*Create Stability PIDS*/
	PID pitchStab;
	PID rollStab;
	PID yawStab;
};
#endif
