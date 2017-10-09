#ifndef stabClass_h
#define stabClass_h

#include "std_msgs/Header.h"
#include "std_msgs/Float32MultiArray.h"
#include "geometry_msgs/Vector3.h"
#include "skyshark_msgs/VelocityTarget.h"
#include "sensor_msgs/Imu.h"
#include "pid.h"
#include "ros/ros.h"

class stabClass
{
	public:
	void rcCallback(const skyshark_msgs::VelocityTarget &message);
	void mpuCallback(const sensor_msgs::Imu &message);
	
	void mapRCval(void);
	void setStabVal(void);
	void computeStab(void);
	
	stabClass();
	
	private:
	float rcX, rcY, rcZ, rcYaw;
	float gyroX, gyroY, gyroZ;
	
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
