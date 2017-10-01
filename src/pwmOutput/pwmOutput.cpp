#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "ros/ros.h"
#include "std_msgs/Float32MultiArray.h"

#include "Navio/PWM.h"
#include "Navio/Util.h"

// Motor numbers definitions
#define MOTOR_FL   0    // Front left    
#define MOTOR_FR   1    // Front right
#define MOTOR_BL   2    // back left
#define MOTOR_BR   3    // back right

class pwmOutput
{
	public:
	pwmOutput();
	void init(void);
	void motorsOff(void);
	void writeMotors(void);
	void stabCallback(const std_msgs::Float32MultiArray::ConstPtr& array);
	
	private:
	PWM motors;
	
	float stabOutput[4];

}

void pwmOutput::stabCallback(const std_msgs::Float32MultiArray::ConstPtr& array)
{
	int i = 0;
	for(std::vector<float>::const_iterator it = array->data.begin(); it != array->data.end(); ++it)
	{
		stabOutput[i] = *it;
		i++;
	}
	
	writeMotors();
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "pwmOutput");
	ros::NodeHandle n;
	pwmOutput OUTPUT;
	
	ros::Subscriber sub = n.subscribe("rcSend", 1000, &pwmOutput::stabCallback, &OUTPUT);
	
	while(true)
	{
		ros::spin();
	}
	
	
	return 0;
}

pwmOutput::init(void)
{
	motors.enable(MOTOR_FL);
	motors.enable(MOTOR_FR);
	motors.enable(MOTOR_BL);
	motors.enable(MOTOR_BR);

	motors.set_period(MOTOR_FL,50);
	motors.set_period(MOTOR_FR,50);
	motors.set_period(MOTOR_BL,50);
	motors.set_period(MOTOR_BR,50);
}

pwmOutput::pwmOutput()
{
	init();
}

pwmOutput::motorsOff(void)
{
	motors.set_duty_cycle(MOTOR_FL,1.000);
	motors.set_duty_cycle(MOTOR_FR,1.000);
	motors.set_duty_cycle(MOTOR_BL,1.000);
	motors.set_duty_cycle(MOTOR_BR,1.000);
}

pwmOutput::writeMotors(void)
{
	motors.set_duty_cycle(MOTOR_FL, stabOutput[0]);
	motors.set_duty_cycle(MOTOR_BL, stabOutput[1]);
	motors.set_duty_cycle(MOTOR_FR, stabOutput[2]);
	motors.set_duty_cycle(MOTOR_BR, stabOutput[3]);
}
