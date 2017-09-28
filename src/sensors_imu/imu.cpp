#include "iostream"
#include "ros/ros.h"

// Message headers
#include "geometry_msgs/Vector3.h"
#include "sensors_imu/RawIMU_9.h"

// Navio headers
#include "Navio/MPU9250.h"
#include "Navio/LSM9DS1.h"
#include "Navio/Util.h"
#include <unistd.h>

int main(int argc, char **argv) {
	// Variables
	float ax, ay, az;
	float gx, gy, gz;
	float mx, my, mz;

	// ROS Stuff
	ros::init(argc, argv, "rcinputRaw");
	ros::NodeHandle n;
	ros::Rate loop_rate(100);

	// Create publishers
	ros::Publisher mpuPub = n.advertise<sensors_imu::RawIMU_9>("mpuRaw", 1000);
	ros::Publisher lsmPub = n.advertise<sensors_imu::RawIMU_9>("lsmRaw", 1000);
	
	// Sensor objects
	InertialSensor *mpu = new MPU9250();
	InertialSensor *lsm = new LSM9DS1();
	
	// TODO: "Probe" Sensors
	
	// Initialize
	mpu->initialize();
	lsm->initialize();

	while(ros::ok()) {
		// Create message objects
		sensors_imu::RawIMU_9 mpuMsg;
		sensors_imu::RawIMU_9 lsmMsg;
		
		// TODO: Add headers or something
		// TODO: Better message objects
		
		// Create the message (MPU)
		mpuMsg.angular_velocity = geometry_msgs::Vector3();
		mpuMsg.linear_acceleration = geometry_msgs::Vector3();
		mpuMsg.compass_orientation = geometry_msgs::Vector3();

		// Read IMU data (MPU)
		mpu->update();
		mpu->read_accelerometer(&ax, &ay, &az);
		mpu->read_gyroscope(&gx, &gy, &gz);
		mpu->read_magnetometer(&mx, &my, &mz);
		
		// Put gyro data in message (MPU)
		mpuMsg.angular_velocity.x = gx;
		mpuMsg.angular_velocity.y = gy;
		mpuMsg.angular_velocity.z = gz;
		
		// Put accelerometer data in message (MPU)
		mpuMsg.linear_acceleration.x = ax;
		mpuMsg.linear_acceleration.y = ay;
		mpuMsg.linear_acceleration.z = az;
		
		// Put magnometer data in message (MPU)
		mpuMsg.compass_orientation.x = mx;
		mpuMsg.compass_orientation.y = my;
		mpuMsg.compass_orientation.z = mz;
		
		// Create the message (LSM)
		lsmMsg.angular_velocity = geometry_msgs::Vector3();
		lsmMsg.linear_acceleration = geometry_msgs::Vector3();
		lsmMsg.compass_orientation = geometry_msgs::Vector3();

		// Read IMU data (LSM)
		lsm->update();
		lsm->read_accelerometer(&ax, &ay, &az);
		lsm->read_gyroscope(&gx, &gy, &gz);
		lsm->read_magnetometer(&mx, &my, &mz);
		
		// Put gyro data in message (LSM)
		lsmMsg.angular_velocity.x = gx;
		lsmMsg.angular_velocity.y = gy;
		lsmMsg.angular_velocity.z = gz;
		
		// Put accelerometer data in message (LSM)
		lsmMsg.linear_acceleration.x = ax;
		lsmMsg.linear_acceleration.y = ay;
		lsmMsg.linear_acceleration.z = az;
		
		// Put magnometer data in message (LSM)
		lsmMsg.compass_orientation.x = mx;
		lsmMsg.compass_orientation.y = my;
		lsmMsg.compass_orientation.z = mz;		

		// Publish messages
		mpuPub.publish(mpuMsg);
		lsmPub.publish(lsmMsg);
		
		// Other ROS maintenance things
		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;
}


