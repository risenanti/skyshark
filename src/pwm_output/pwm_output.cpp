#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "ros/ros.h"
#include "std_msgs/Header.h"
#include "std_msgs/Float32MultiArray.h"
#include "skyshark_msgs/RotorSpeeds.h"

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
	void printStab(void);
	void stabCallback(const skyshark_msgs::RotorSpeeds &speed);
	
	private:
	PWM motors;
	
	float stabOutput[4];

};

void pwmOutput::stabCallback(const skyshark_msgs::RotorSpeeds &speed)
{
	stabOutput[0] = speed.rotor1;
	stabOutput[1] = speed.rotor2;
	stabOutput[2] = speed.rotor3;
	stabOutput[3] = speed.rotor4;
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "pwmOutput");
	ros::NodeHandle n;
	
	ros::Rate loop_rate(10); /*10 HZ*/
	
	pwmOutput OUTPUT;
	
	if (check_apm()) {
        return 1;
    }
    
    OUTPUT.init();
	
	ros::Subscriber sub = n.subscribe("stabOutput", 1000, &pwmOutput::stabCallback, &OUTPUT);
	
	while(true)
	{
		//OUTPUT.printStab();
		ros::spinOnce();
		OUTPUT.writeMotors();
		loop_rate.sleep();
	}
	
	
	return 0;
}

void pwmOutput::init(void)
{
	
	if(!motors.init(MOTOR_FL))
	{
		fprintf(stderr, "Output Enable not set. Are you root?\n");
        return;
	}
	if(!motors.init(MOTOR_FR))
	{
		fprintf(stderr, "Output Enable not set. Are you root?\n");
        return;
	}
	if (!motors.init(MOTOR_BL))
	{
		fprintf(stderr, "Output Enable not set. Are you root?\n");
        return;
	}
	
	if (!motors.init(MOTOR_BR))
	{
		fprintf(stderr, "Output Enable not set. Are you root?\n");
        return;
	}
	
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

void pwmOutput::motorsOff(void)
{
	motors.set_duty_cycle(MOTOR_FL,1.000);
	motors.set_duty_cycle(MOTOR_FR,1.000);
	motors.set_duty_cycle(MOTOR_BL,1.000);
	motors.set_duty_cycle(MOTOR_BR,1.000);
}

void pwmOutput::writeMotors(void)
{
	motors.set_duty_cycle(MOTOR_FL, stabOutput[0]);
	motors.set_duty_cycle(MOTOR_BL, stabOutput[1]);
	motors.set_duty_cycle(MOTOR_FR, stabOutput[2]);
	motors.set_duty_cycle(MOTOR_BR, stabOutput[3]);
}

void pwmOutput::printStab(void)
{
	printf("%f %f %f %f \n", stabOutput[0], stabOutput[1], stabOutput[2], stabOutput[3]);
}
