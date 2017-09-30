/*KEITH CONLEY
**USM
**FALL 2018
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
double pitch_stab_output, roll_stab_output, yaw_stab_output;
double pidRollStab, pidRollStabOut;

volatile int rawInput1; //throttle from controller
volatile int rawInput2; //roll
volatile int rawInput3; //pitch
volatile int rawInput4; //yaw

//PID pitchRate (&input, &output,              &setpoint,   0.7, 1.0, 0.0, DIRECT);
//PID rollRate  (&input, &output,              &setpoint,   0.7, 1.0, 0.0, DIRECT);
PID pitchStab (&pitch, &pitch_stab_output,   &rcpit,      4.5, 0.0, 0.0, DIRECT);
PID rollStab  (&roll,  &roll_stab_output,    &rcroll,     4.5, 0.0, 0.0, DIRECT);
//PID yawRate   (&input, &output,              &setpoint,   2.7, 1.0, 0.0, DIRECT);
PID yawStab   (&yaw,   &yaw_stab_output,     &yaw_target, 10.0, 0.0, 0.0, DIRECT);

PWM motors;

int main(int argc, char **argv)
{
	InertialSensor *sensor;
	sensor = new MPU9250();
	createMillisTimer(); //create timer

	if(check_apm()) { return 1;}
	
	rcin.init();
	sensor->initialize();
	
	enableMotors();
	
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
			//pidPitchStab = rcpit-pitch;
			//pitchStab.Compute();
			//double piStabOut = constrain(pidPitchStabOut,-250,250);
			
			//pidRollStab = rcroll - roll;
			//rollStab.Compute();
			//double piRollStabOut = constrain (pidRollStabOut, -250, 250);
			
		}
		
		else {
			motorsOff();
			yaw_target = yaw;
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
	roll  = gx; //measured values inputs to PID
	pitch = gy;
	yaw   = gz; 
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
	motors.set_duty_cycle(MOTOR_FL,1000);
	motors.set_duty_cycle(MOTOR_FR,1000);
	motors.set_duty_cycle(MOTOR_BL,1000);
	motors.set_duty_cycle(MOTOR_BR,1000);
}

void writeStableMotors(void)
{
//	motors.set_duty_cycle(MOTOR_FL, rcthr + roll_output + pitch_output - yaw_output);
//    motors.set_duty_cycle(MOTOR_BL, rcthr + roll_output - pitch_output + yaw_output);
//   motors.set_duty_cycle(MOTOR_FR, rcthr - roll_output + pitch_output + yaw_output);
//    motors.set_duty_cycle(MOTOR_BR, rcthr - roll_output - pitch_output - yaw_output);
}
