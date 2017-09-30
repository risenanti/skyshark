#include "ros/ros.h"

// Message headers
#include "std_msgs/Header.h"
#include "sensor_msgs/Imu.h"
#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Quaternion.h"

// Navio headers
#include "Navio/MPU9250.h"
#include "Navio/LSM9DS1.h"
#include "Navio/Util.h"
#include <unistd.h>

void imuPublisher(ros::Publisher& publisher, InertialSensor* sensor) {
	// Variables
	float ax, ay, az;
	float gx, gy, gz;
	float mx, my, mz;

	// Create message object
	sensor_msgs::Imu message;
	
	// Build the message
	message.header = std_msgs::Header();
	message.header.stamp = ros::Time::now();
	
	message.orientation = geometry_msgs::Quaternion();
	message.orientation_covariance = {-1, 0, 0, 0, 0, 0, 0, 0, 0};
	
	message.angular_velocity = geometry_msgs::Vector3();
	message.angular_velocity_covariance = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	
	message.linear_acceleration = geometry_msgs::Vector3();
	message.linear_acceleration_covariance = {0, 0, 0, 0, 0, 0, 0, 0, 0};

	// Read IMU data
	sensor->read_accelerometer(&ax, &ay, &az);
	sensor->read_gyroscope(&gx, &gy, &gz);
	sensor->read_magnetometer(&mx, &my, &mz);
	
	// Put gyro data in message
	message.angular_velocity.x = gx;
	message.angular_velocity.y = gy;
	message.angular_velocity.z = gz;
	
	// Put accelerometer data in message
	message.linear_acceleration.x = ax;
	message.linear_acceleration.y = ay;
	message.linear_acceleration.z = az;

	// Publish message
	publisher.publish(message);
}

/*
void compassPublisher(ros::Publisher& publisher, InertialSensor* sensor) {
	// Variables
	float mx, my, mz;
	
	// Build the message
	message.header = std_msgs::Header();
	mpuMsg.compass_orientation = geometry_msgs::Vector3();

	// Read IMU data (MPU)
	sensor->read_magnetometer(&mx, &my, &mz);
	
	// Put magnometer data in message
	message.compass_orientation.x = mx;
	message.compass_orientation.y = my;
	message.compass_orientation.z = mz;

	// Publish message
	publisher.publish(message);
}

void temperaturePublisher() {
}
*/

int main(int argc, char **argv) {
	// ROS Stuff
	ros::init(argc, argv, "imuRaw");
	ros::NodeHandle n;
	ros::Rate loop_rate(100);

	// Create publishers
	ros::Publisher mpuPublisher = n.advertise<sensor_msgs::Imu>("mpuRaw", 1000);
	ros::Publisher lsmPublisher = n.advertise<sensor_msgs::Imu>("lsmRaw", 1000);
	
	// Sensor objects
	InertialSensor *mpu = new MPU9250();
	InertialSensor *lsm = new LSM9DS1();
	
	// Initialize
	mpu->initialize();
	lsm->initialize();

	while(ros::ok()) {
		// MPU9250
		mpu->update();
		imuPublisher(mpuPublisher, mpu);
		
		// LSM9DS1
		lsm->update();
		imuPublisher(lsmPublisher, lsm);
		
		// Other ROS maintenance things
		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;
}


