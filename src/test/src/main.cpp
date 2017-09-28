/*KEITH CONLEY
**USM
**FALL 2018
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "pid.h"
#include "millis.h"

#include "Navio/RCInput.h"
#include "Navio/Util.h"
#include "Navio/MPU9250.h"
#include "Navio/LSM9DS1.h"
#include "Navio/PWM.h"

#define MOTOR1 0
#define MOTOR2 1
#define MOTOR3 2
#define MOTOR4 3

// Radio min/max values for each stick for my radio (worked out at beginning of article)
#define RC_THR_MIN   1070
#define RC_YAW_MIN   1068
#define RC_YAW_MAX   1915
#define RC_PIT_MIN   1077
#define RC_PIT_MAX   1915
#define RC_ROL_MIN   1090
#define RC_ROL_MAX   1913

// Motor numbers definitions
#define MOTOR_FL   2    // Front left    
#define MOTOR_FR   0    // Front right
#define MOTOR_BL   1    // back left
#define MOTOR_BR   3    // back right

// Arduino map function
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

double constrain(double x, double a, double b) {
    if(x < a) {
        return a;
    }
    else if(b < x) {
        return b;
    }
    else
        return x;
}


#define wrap_180(x) (x < -180 ? x+360 : (x > 180 ? x - 360: x))

// PID array (6 pids, two for each axis)
//double input,output,setpoint,kp,ki,kd;
#define PID_PITCH_RATE 0
#define PID_ROLL_RATE 1
#define PID_PITCH_STAB 2
#define PID_ROLL_STAB 3
#define PID_YAW_RATE 4
#define PID_YAW_STAB 5

double input, output, setpoint;
long rcthr, rcyaw, rcpit, rcroll;
double pidPitchStab, pidPitchStabOut;
double pidRollStab, pidRollStabOut;

//PID pitchRate (&input, &output, &setpoint, 0.7 , 1.0, 0.0, DIRECT);
//PID rollRate  (&input, &output, &setpoint, 0.7 , 1.0, 0.0, DIRECT);
PID pitchStab (&pidPitchStab, &pidPitchStabOut, 1.0, 4.5 , 0.0, 0.0, DIRECT);
PID rollStab  (&pidRollStab, &pidRollStabOut, 1.0, 0.0 , 0.0, 0.0, DIRECT);
//PID yawRate   (&input, &output, &setpoint, 2.7 , 1.0, 0.0, DIRECT);
//PID yawStab   (&input, &output, &setpoint, 10.0, 0.0, 0.0, DIRECT);

PWM motors;

int main(int argc, char **argv)
{
	RCInput rcin;
	InertialSensor *sensor;
	sensor = new MPU9250();
	createMillisTimer(); //create timer

	if(check_apm()) { return 1;}
	
	rcin.init();
	sensor->initialize();
	
	float gx; //ROLL
	float gy; //PITCH 
	float gz; //YAW
	
	motors.enable(MOTOR1);
	motors.enable(MOTOR2);
	motors.enable(MOTOR3);
	motors.enable(MOTOR4);

	motors.set_period(MOTOR1,50);
	motors.set_period(MOTOR2,50);
	motors.set_period(MOTOR3,50);
	motors.set_period(MOTOR4,50);
	
	while (1)
	{
		static double yaw_target = 0;  
		sensor->update();
	    //shove gyroscope data straight into pid
        sensor->read_gyroscope(&gx, &gy, &gz);
		/*array element 0 left stick up and down*/
		volatile int rawInput1 = rcin.read(0); //throttle from controller
		volatile int rawInput2 = rcin.read(1); //roll
		volatile int rawInput3 = rcin.read(2); //pitch
		volatile int rawInput4 = rcin.read(3); //yaw
		
		rcthr = rawInput1;
		rcyaw = map(rawInput4, RC_YAW_MIN, RC_YAW_MAX, -180, 180);
		rcpit = map(rawInput3, RC_PIT_MIN, RC_PIT_MAX, -45, 45);
		rcroll = map(rawInput2, RC_ROL_MIN, RC_ROL_MAX, -45, 45);
		double roll  = gx;
		double pitch = gy;
		double yaw   = gz; 	
		
		if(rcthr > RC_THR_MIN + 100) 
		{  // Throttle raised, turn on stablisation.
			pidPitchStab = rcpit-pitch;
			pitchStab.Compute();
			double piStabOut = constrain(pidPitchStabOut,-250,250);
			
			pidRollStab = rcroll - roll;
			rollStab.Compute();
			double piRollStabOut = constrain (pidRollStabOut, -250, 250);
			
		}
		
		else {
			motors.set_duty_cycle(MOTOR1,1000);
			motors.set_duty_cycle(MOTOR2,1000);
			motors.set_duty_cycle(MOTOR3,1000);
			motors.set_duty_cycle(MOTOR4,1000);
			
			yaw_target = yaw;
		}
		
		usleep(1000);
	}
	
	return 0;
}
