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

#define wrap_180(x) (x < -180 ? x+360 : (x > 180 ? x - 360: x))

// PID array (6 pids, two for each axis)
double input,output,setpoint,kp,ki,kd;
PID pids(&input,&output,&setpoint,(double)0.02,(double)1.0,(double)0.01, DIRECT);
#define PID_PITCH_RATE 0
#define PID_ROLL_RATE 1
#define PID_PITCH_STAB 2
#define PID_ROLL_STAB 3
#define PID_YAW_RATE 4
#define PID_YAW_STAB 5

int main(int argc, char **argv)
{
	RCInput rcin;
	InertialSensor *sensor;
	sensor = new MPU9250();
	createMillisTimer(); //create timer

	if(check_apm()) { return 1;}
	
	rcin.init();
	sensor->initialize();
	
	float ax, ay, az;
	float gx, gy, gz;
	
	/*pwm.enable(MOTOR1);
	pwm.enable(MOTOR2);
	pwm.enable(MOTOR3);
	pwm.enable(MOTOR4);

	pwm.set_period(MOTOR1,50);
	pwm.set_period(MOTOR2,50);
	pwm.set_period(MOTOR3,50);
	pwm.set_period(MOTOR4,50);
	*/
	
	while (1)
	{
		sensor->update();
	    sensor->read_accelerometer(&ax, &ay, &az);
        sensor->read_gyroscope(&gx, &gy, &gz);
		/*array element 0 left stick up and down*/
		volatile int rawInput1 = rcin.read(0); //read throttle from controller
		
		usleep(1000);
	}
	
	return 0;
}
