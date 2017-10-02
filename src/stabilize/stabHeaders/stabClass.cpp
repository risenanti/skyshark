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
}
