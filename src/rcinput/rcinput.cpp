// System headers
#include <iostream>

// ROS headers
#include "ros/ros.h"

// Message headers
#include "geometry_msgs/Vector3.h"
#include "rcinput/VelocityControlTarget.h"

// Navio headers
#include "Navio/RCInput.h"
#include "Navio/Util.h"

/* Turnigy 9XR Bindings
 * 
 * 		Channels:
 * 			0 | Left stick vertical			| z
 * 			1 | Right stick horizontal		| y
 * 			2 | Right stick vertical		| x
 * 			3 | Left stick horizontal		| yaw
 * 
 */
void turnigyPublisher(ros::Publisher& publisher, RCInput rc) {
	// Variables
	int x, y, z;
	static int dYaw; // To maintain internal state, for integration
	
	// Create message object
	rcinput::VelocityControlTarget message;
	
	// Build the message
	message.velocity = geometry_msgs::Vector3();

	// Read controller data
	// TODO: Add raw controller input somewhere in here
	// TODO: Convert to [-1.0, +1.0] values
	x = rc.read(2);
	y = rc.read(1);
	z = rc.read(0);
	dYaw = rc.read(3);
	
	// Put data in message
	message.velocity.x = x;
	message.velocity.y = y;
	message.velocity.z = z;
	//message.yaw = yaw;

	// Publish message
	publisher.publish(message);
}

int main(int argc, char **argv) {
	// ROS stuff
	ros::init(argc, argv, "rcinputRaw");
	ros::NodeHandle n;
	ros::Rate loop_rate(10);
	
	// Create publishers
	ros::Publisher rcPublisher = n.advertise<rcinput::VelocityControlTarget>("velocityControl", 1000);

	// Sensor objects
	RCInput rc;
	rc.init();

	while(ros::ok()) {
		// Controller
		turnigyPublisher(rcPublisher, rc);
		
		// Other ROS maintenance things
		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;
}


