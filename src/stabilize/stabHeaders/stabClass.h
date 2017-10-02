#ifndef stabClass_h
#define stabClass_h

#include "std_msgs/Header.h"
#include "std_msgs/Float32MultiArray.h"
#include "geometry_msgs/Vector3.h"
#include "skyshark_msgs/VelocityTarget.h"
#include "sensor_msgs/Imu.h"

#include "pid.h"

class stabClass
{
	public:
	void rcCallback(const skyshark_msgs::VelocityTarget &message);
	void mpuCallback(const sensor_msgs::Imu &message);
	
	private:
	float rcX, rcY, rcZ, rcYaw;
	float gyroX, gyroY, gyroZ;
	
};

#endif
