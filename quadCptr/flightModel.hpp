#ifndef flightModel_HPP
#define flightModel_HPP

#include <unistd.h>
#include "Navio/RGBled.h"
#include "Navio/PWM.h"
#include "Navio/RCInput.h"
#include "Navio/Util.h"
#include <stdio.h>

#include "ros/ros.h"
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Float32MultiArray.h"

#define MOTOR1 0
#define MOTOR2 1
#define MOTOR3 2
#define MOTOR4 3

class flightModel
{
	public:
	
	flightModel(void);
	
	void rcCallback(const std_msgs::Float32MultiArray::ConstPtr& array);
	
	/*Process Input FUnction*/
	//TODO IMPLEMENT
	int processControlInput(void);
	
	/*Motor Control Functions*/
	int pwmInit(void);
	
	int setPWMdutyCycle(float x);
	int motorOnePWM(float x);
	int motorTwoPWM(float x);
	int motorThreePWM(float x);
	int motorFourPWM(float x);
	
	int throttleUp(float magnitude);
	
	int moveLeft(float magnitude);
	int moveRight(float magnitude);
	
	int moveForward(float magnitude);
	int moveBackward(float magnitude);
		
	int turnClockwise(float magnitude);
	int turnCounterClockwise(float magnitude);
	
	int setMotors(void);
	
	/*End control Functions*/
	
	private:
	
	/*Callback Array*/
	float data[7];
	
	/*Variables to pass to motors*/
	float motorOneDuty;
	float motorTwoDuty;
	float motorThreeDuty;
	float motorFourDuty;
	
	float leftRightSwitch;
	float forwardBackwardSwitch;
	float clockCounterClockSwitch;
	
	float ThrottleMagnitude;
	float LeftRightMagnitude;
	float ForwardBackMagnitude;
	float ClockCounterMagnitude;
	
	/*Motor Control PWM*/
	PWM pwm;
};

//TODO NEEDS WORK
void flightModel::rcCallback(const std_msgs::Float32MultiArray::ConstPtr& array)
{
	int i = 0;
	for(std::vector<float>::const_iterator it = array->data.begin(); it != array->data.end(); ++it)
	{
		data[i] = *it;
		i++;
	}
	
	ThrottleMagnitude       = data[0];
	
	leftRightSwitch         = data[1];
	LeftRightMagnitude      = data[2];
	
	forwardBackwardSwitch   = data[3];
	ForwardBackMagnitude    = data[4];
	
	clockCounterClockSwitch = data[5];
	ClockCounterMagnitude   = data[6];
	
	/*for(int i = 0; i < 7;i++)
	{
		printf("%f, ", data[i]);
	}
	printf("\n");*/
	
	processControlInput();
}

flightModel::flightModel(void)
{
	if(check_apm()) 
	{ 
		ROS_INFO("ERROR!!!!");
	}
	
	leftRightSwitch = 0.0;
	forwardBackwardSwitch=0.0;
	clockCounterClockSwitch=0.0;
	
	ThrottleMagnitude=0.0;
	LeftRightMagnitude=0.0;
	ForwardBackMagnitude=0.0;
	ClockCounterMagnitude=0.0;
	
	pwmInit();
}

int flightModel::pwmInit(void)
{
	
	if (!(pwm.init(MOTOR1) && pwm.init(MOTOR2) && pwm.init(MOTOR3) && pwm.init(MOTOR4)))
	{
		ROS_INFO("OUTPUT ENABLE NOT SET. Are you root?\n");
		return 0;
	}
	
	pwm.enable(MOTOR1);
	pwm.enable(MOTOR2);
	pwm.enable(MOTOR3);
	pwm.enable(MOTOR4);

	pwm.set_period(MOTOR1,50);
	pwm.set_period(MOTOR2,50);
	pwm.set_period(MOTOR3,50);
	pwm.set_period(MOTOR4,50);
	
	return 0;
}

int flightModel::setPWMdutyCycle(float x)
{
	pwm.set_duty_cycle(MOTOR1, x);
	pwm.set_duty_cycle(MOTOR2, x);
	pwm.set_duty_cycle(MOTOR3, x);
	pwm.set_duty_cycle(MOTOR4, x);
	return 1;
}

int flightModel::motorOnePWM(float x)
{
	pwm.set_duty_cycle(MOTOR1, x);
	return 1;
}

int flightModel::motorTwoPWM(float x)
{
	pwm.set_duty_cycle(MOTOR2, x);
	return 1;
}
int flightModel::motorThreePWM(float x)
{
	pwm.set_duty_cycle(MOTOR3, x);
	return 1;
}
int flightModel::motorFourPWM(float x)
{
	pwm.set_duty_cycle(MOTOR4, x);
	return 1;
}

int flightModel::throttleUp(float magnitude)
{
	motorOneDuty = magnitude;
	motorTwoDuty = magnitude;
	motorThreeDuty = magnitude;
	motorFourDuty = magnitude;
	return 1;
}
	
	/*float leftRightSwitch;
	  float forwardBackwardSwitch;
	  float clockCounterClockSwitch;
	*/
	/*Motor 1 and Motor 3 spin counter Clockwise*/
	/*Motor 2 and Motor 4 spin clockwise*/
	
int flightModel::moveLeft(float magnitude)
{
	motorOneDuty  = motorOneDuty  - magnitude;
	motorFourDuty = motorFourDuty - magnitude;
	return 1;
}

int flightModel::moveRight(float magnitude)
{
	motorTwoDuty   = motorTwoDuty   - magnitude;
	motorThreeDuty = motorThreeDuty - magnitude;
	return 1;
}
	
int flightModel::moveForward(float magnitude)
{
	motorOneDuty  = motorOneDuty  - magnitude;
	motorTwoDuty  = motorTwoDuty - magnitude;
	return 1;
}

int flightModel::moveBackward(float magnitude)
{
	motorThreeDuty  = motorThreeDuty  - magnitude;
	motorFourDuty   = motorFourDuty   - magnitude;
	return 1;
}
		
int flightModel::turnClockwise(float magnitude)
{
	motorOneDuty    = motorOneDuty   - magnitude;
	motorThreeDuty  = motorThreeDuty - magnitude;
	return 1;
}

int flightModel::turnCounterClockwise(float magnitude)
{
	motorTwoDuty    = motorTwoDuty   - magnitude;
	motorFourDuty   = motorFourDuty  - magnitude;
	return 1;
}

int flightModel::setMotors(void)
{
	motorOnePWM  (motorOneDuty);
	motorTwoPWM  (motorTwoDuty);
	motorThreePWM(motorThreeDuty);
	motorFourPWM (motorFourDuty);
	return 1;
}

	/*
	 * float leftRightSwitch;  
	 *    0 means RIGHT 1 means LEFT -1 means neutral
	 * 
	 * float forwardBackwardSwitch; 
	 *    0 means BACKWARD 1 means FORWARD -1 means neutral
	 * 
	 * float clockCounterClockSwitch; 
	 *    0 means COUNTERCLOCK 1 means CLOCK -1 means neutral
	 *        
	*/
	/*Motor 1 and Motor 3 spin counter Clockwise*/
	/*Motor 2 and Motor 4 spin clockwise*/
	
int flightModel::processControlInput(void)
{
	throttleUp(ThrottleMagnitude);
	
	switch((int)leftRightSwitch)
	{
		case -1 :   /*Neutral Stick Case*/
					break;
					
		case  0 :    moveRight(LeftRightMagnitude);
		            break;
		            
		case  1 :    moveLeft(LeftRightMagnitude);
		            break;
		            
		default :   ROS_INFO("ERROR LEFT RIGHT SWITCH"); 
					break;
	}
	
	switch((int)forwardBackwardSwitch)
	{
		case -1 :   /*Neutral Stick Case*/
					break;
					
		case  0 :    moveBackward(ForwardBackMagnitude);
		            break;
		            
		case  1 :    moveForward(ForwardBackMagnitude);
		            break;
		            
		default :   ROS_INFO("ERROR FORWARD BACKWARD SWITCH"); 
					break;
	}
	
	switch((int)clockCounterClockSwitch)
	{
		case -1:   /*Neutral Stick Case*/
					break;
					
		case  0 :   turnCounterClockwise(ClockCounterMagnitude);
		            break;
		            
		case  1 :   turnClockwise(ClockCounterMagnitude);
		            break;
		            
		default :   ROS_INFO("ERROR CLOCK COUNTERCLOCK SWITCH"); 
					break;
	}
	
	setMotors();
	
	return 1;
}

#endif
