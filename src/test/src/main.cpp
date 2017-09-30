/*KEITH CONLEY
**USM
**FALL 2018
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "pid.h"
#include "millis.h"
#include "rcDef.h"

#include "Navio/RCInput.h"
#include "Navio/Util.h"
#include "Navio/MPU9250.h"
#include "Navio/LSM9DS1.h"
#include "Navio/PWM.h"

void enableMotors(void);
void motorsOff(void);
void writeStableMotors(void); //write stablization to motors

RCInput rcin;
void readRCin(void); //read raw rc val

double rcthr, rcyaw, rcpit, rcroll;
void mapRCval(void); //map values to rc var in degrees

void setStabVal(void); //set pid inputs to new data
float gx; //ROLL
float gy; //PITCH 
float gz; //YAW

double roll; //measured values inputs to PID
double pitch;
double yaw; 	

static double yaw_target;

volatile int rawInput1; //throttle from controller
volatile int rawInput2; //roll
volatile int rawInput3; //pitch
volatile int rawInput4; //yaw

int main(int argc, char **argv)
{
	InertialSensor *sensor;
	sensor = new MPU9250();
	createMillisTimer(); //create timer

	if(check_apm()) { return 1;}
	
	rcin.init();
	sensor->initialize();
	
	PWM motors;
	motors.enable(MOTOR_FL);
	motors.enable(MOTOR_FR);
	motors.enable(MOTOR_BL);
	motors.enable(MOTOR_BR);

	motors.set_period(MOTOR_FL,50);
	motors.set_period(MOTOR_FR,50);
	motors.set_period(MOTOR_BL,50);
	motors.set_period(MOTOR_BR,50);
	
	/*Create and setup PIDS*/
	PID pitchRate;
			pitchRate.SetTunings(0.70, 1.00, 0.00);
			pitchRate.setImax(50.00);
	PID pitchStab;
			pitchStab.SetTunings(4.50, 0.00, 0.00);
	PID rollRate;
			rollRate.SetTunings(0.700, 1.00, 0.00);
			rollRate.setImax(50);
	PID rollStab;
			rollStab.SetTunings(4.500, 0.00, 0.00);
	PID yawRate;
			yawRate.SetTunings(2.70, 1.00, 0.00);
			yawRate.setImax(50.00);
	PID yawStab;
			yawStab.SetTunings(10.00, 0.00, 0.00);
	/*END PID SETUP*/
	
	while (1)
	{
		yaw_target = 0;  
		sensor->update();
	    //shove gyroscope data straight into pid
        sensor->read_gyroscope(&gx, &gy, &gz);
		/*array element 0 left stick up and down*/
		readRCin();
		mapRCval();
		
		setStabVal();	
		
		if(rcthr > RC_THR_MIN + 100) 
		{  // Throttle raised, turn on stablisation.
				
		float pitch_stab_output = constrain(pitchStab.getPID((float)rcpit - pitch), -250, 250); 
		float roll_stab_output = constrain(rollStab.getPID((float)rcroll - roll), -250, 250);
		float yaw_stab_output = constrain(yawStab.getPID(wrap_180(yaw_target - yaw)), -360, 360);
  
		//if pilot asking for yaw change feed directly to rate pid (overwriting yaw stab output)
		//side note: cheating PID
		if(abs(rcyaw ) > 5) {
		  yaw_stab_output = rcyaw;
		  yaw_target = yaw;   // remember this yaw for when pilot stops
		}
		
		// rate PIDS
		long pitch_output =  (long) constrain(pitchRate.getPID(pitch_stab_output - pitch), - 500, 500);  
		long roll_output =  (long) constrain(rollRate.getPID(roll_stab_output - roll), -500, 500);  
		long yaw_output =  (long) constrain(yawRate.getPID(yaw_stab_output - yaw), -500, 500);  
		
		motors.set_duty_cycle(MOTOR_FL, (float)(rcthr + roll_output + pitch_output - yaw_output)/1000);
		motors.set_duty_cycle(MOTOR_BL, (float)(rcthr + roll_output - pitch_output + yaw_output)/1000);
		motors.set_duty_cycle(MOTOR_FR, (float)(rcthr - roll_output + pitch_output + yaw_output)/1000);
		motors.set_duty_cycle(MOTOR_BR, (float)(rcthr - roll_output - pitch_output - yaw_output)/1000);
		
		float s  = (rcthr + roll_output + pitch_output - yaw_output)/1000;
		printf("%f\n",s);
		}
		
		else {
			motors.set_duty_cycle(MOTOR_FL,1.000);
			motors.set_duty_cycle(MOTOR_FR,1.000);
			motors.set_duty_cycle(MOTOR_BL,1.000);
			motors.set_duty_cycle(MOTOR_BR,1.000);
			yaw_target = yaw;
			pitchRate.resetI();
			yawRate.resetI();
			rollRate.resetI();
		}
	}
	
	return 0;
}

void readRCin(void)
{
		rawInput1 = rcin.read(0); //throttle from controller
		rawInput2 = rcin.read(1); //roll
		rawInput3 = rcin.read(2); //pitch
		rawInput4 = rcin.read(3); //yaw
}

void mapRCval(void)
{
	rcthr = rawInput1;
	rcyaw = map(rawInput4, RC_YAW_MIN, RC_YAW_MAX, -180, 180);
	rcpit = map(rawInput3, RC_PIT_MIN, RC_PIT_MAX, -45, 45);
	rcroll = map(rawInput2, RC_ROL_MIN, RC_ROL_MAX, -45, 45);
}

void setStabVal(void)
{
	roll  = gx*(double)180/M_PI; //measured values inputs to PID converted from radians to degrees
	pitch = gy*(double)180/M_PI;
	yaw   = gz*(double)180/M_PI; 
}

void enableMotors(void)
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

void motorsOff(void)
{
	motors.set_duty_cycle(MOTOR_FL,1.000);
	motors.set_duty_cycle(MOTOR_FR,1.000);
	motors.set_duty_cycle(MOTOR_BL,1.000);
	motors.set_duty_cycle(MOTOR_BR,1.000);
}

void writeStableMotors(void)
{
//	motors.set_duty_cycle(MOTOR_FL, rcthr + roll_output + pitch_output - yaw_output);
//    motors.set_duty_cycle(MOTOR_BL, rcthr + roll_output - pitch_output + yaw_output);
//   motors.set_duty_cycle(MOTOR_FR, rcthr - roll_output + pitch_output + yaw_output);
//    motors.set_duty_cycle(MOTOR_BR, rcthr - roll_output - pitch_output - yaw_output);
}

