/*Copyright Jackal Robotics LLC*/
/*Keith Conley 2017*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "ros/ros.h"

#include "std_msgs/Header.h"
#include "sensor_msgs/Imu.h"
#include "skyshark_msgs/frameAngle.h"

#define degConvert 57.2957786

class complimentaryFilter
{
	public:
	void mpuCallback(const sensor_msgs::Imu &message);
	void calibrateIMU(void);
	
	/*set data as needed*/
	void processInputs(void);
	
	/*change the imu output to frame orientation in degrees*/
	void degSecCompute(void);
	
	/*getters*/
	float getRoll(void);
	float getPitch(void);
	float getYaw(void);
	
	private:
	sensor_msgs::Imu mpuRaw;
	skyshark_msgs::frameAngle angle;
	
	float roll, pitch, yaw;
	
	//pitch is y
	float pitchGyro;
	float pitchAccel;
	//roll is x
	float rollGyro;
	float rollAccel;
	//yaw is z
	float yawGyro;
	float yawAccel;
};

int main(int argc, char **argv)
{
	ros::init(argc, argv, "imu_filter");
	
	complimentaryFilter filter;
	
	ros::NodeHandle n;
	ros::Rate loop_rate(500); /*500 HZ*/
	ros::Subscriber nSub = n.subscribe("mpuRaw", 1000, &complimentaryFilter::mpuCallback, &filter);
	
	ros::NodeHandle z;
	ros::Publisher frameAngleOut = z.advertise<skyshark_msgs::frameAngle>("frame_angle",1000);
	skyshark_msgs::frameAngle angle;
	
	while(1)
	{
		ros::spinOnce();
		filter.degSecCompute();
		
		angle.rollAngle = filter.getRoll();
		angle.pitchAngle = filter.getPitch();
		angle.yawAngle = filter.getYaw();
		
		frameAngleOut.publish(angle);
			
		loop_rate.sleep();	
	}
	
	return 0;
}
#define dt 0.002
void complimentaryFilter::degSecCompute(void)
{
	processInputs();
	angle.rollAngle = 0.99 * (angle.rollAngle + rollGyro * dt) + 0.01 * roll;
	angle.pitchAngle = 0.99 * (angle.pitchAngle + pitchGyro * dt) + 0.01 * pitch;
	angle.yawAngle = yawAccel;//actually accel; angle cannot be measured without magnometer
}

void complimentaryFilter::processInputs(void)
{
	/*divide by 131.0 to convert to deg/sec*/
	//pitch is y
	pitchGyro = mpuRaw.angular_velocity.y/131.0;
	pitchAccel = mpuRaw.linear_acceleration.y;
	//roll is x
	rollGyro = mpuRaw.angular_velocity.x/131.0;
	rollAccel = mpuRaw.linear_acceleration.x;
	//yaw is z
	yawGyro = mpuRaw.angular_velocity.z/131.0;
	yawAccel = mpuRaw.linear_acceleration.z;
	
	roll = atan2(pitchAccel, yawAccel) * degConvert;
	pitch = atan2(-rollAccel, yawAccel) * degConvert;
}

float complimentaryFilter::getRoll(void)
{
	return angle.rollAngle;
}
float complimentaryFilter::getPitch(void)
{
	return angle.pitchAngle;
}
float complimentaryFilter::getYaw(void)
{
	return angle.yawAngle;
}

void complimentaryFilter::mpuCallback(const sensor_msgs::Imu &message)
{
	mpuRaw.angular_velocity.x = message.angular_velocity.x;
	mpuRaw.angular_velocity.y = message.angular_velocity.y;
	mpuRaw.angular_velocity.z = message.angular_velocity.z;
	
	mpuRaw.linear_acceleration.x = message.linear_acceleration.x;
	mpuRaw.linear_acceleration.y = message.linear_acceleration.y;
	mpuRaw.linear_acceleration.z = message.linear_acceleration.z;
}

/*Copyright Jackal Robotics LLC*/
/*Keith Conley 2017*/
