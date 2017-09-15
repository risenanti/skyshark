#include <stdio.h>
#include <stdlib.h>

#include "Navio/RCInput.h"
#include "Navio/Util.h"
#include "Navio/MPU9250.h"
#include "Navio/LSM9DS1.h"
#include "Navio/PWM.h"
#include <unistd.h>

//#include <PID.h>

#define MOTOR1 0
#define MOTOR2 1
#define MOTOR3 2
#define MOTOR4 3

PWM pwm;

#define wrap_180(x) (x < -180 ? x+360 : (x > 180 ? x - 360: x))

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int main(int argc, char **argv)
{
	RCInput rcin;
	InertialSensor *sensor;
	sensor = new MPU9250();

	if(check_apm()) { return 1;}
	
	rcin.init();
	sensor->initialize();
	
	float ax, ay, az;
	float gx, gy, gz;
	float mx, my, mz;
	
	pwm.enable(MOTOR1);
	pwm.enable(MOTOR2);
	pwm.enable(MOTOR3);
	pwm.enable(MOTOR4);

	pwm.set_period(MOTOR1,50);
	pwm.set_period(MOTOR2,50);
	pwm.set_period(MOTOR3,50);
	pwm.set_period(MOTOR4,50);
	
	while (1)
	{
		sensor->update();
	        sensor->read_accelerometer(&ax, &ay, &az);
        	sensor->read_gyroscope(&gx, &gy, &gz);
        	sensor->read_magnetometer(&mx, &my, &mz);
		/*array element 0 left stick up and down*/
		volatile int rawInput1 = rcin.read(0);
		printf("%f\n",az);
		usleep(100000);
		
	}
	
	return 0;
}
