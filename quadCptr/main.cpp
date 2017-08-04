#include <unistd.h>
#include "Navio/RGBled.h"
#include "Navio/PWM.h"
#include "Navio/Util.h"
#include <stdio.h>

#define MOTOR1 0
#define MOTOR2 1
#define MOTOR3 2
#define MOTOR4 3

#define SERVO_MIN 1.250 /*MS*/
#define SERVO_MAX 1.750 /*MS*/

int main()
{
	RGBled led;
	PWM pwm;

	if(check_apm()) { return 1;}

	if (!led.initialize()) return EXIT_FAILURE;
	if (!(pwm.init(MOTOR1) && pwm.init(MOTOR2) && pwm.init(MOTOR3) && pwm.init(MOTOR4)))
	{
		fprintf(stderr,"OUTPUT ENABLE NOT SET. Are you root?\n");
		return 0;
	}

	led.setColor(Colors::Yellow);
	pwm.enable(MOTOR1);
	pwm.enable(MOTOR2);
	pwm.enable(MOTOR3);
	pwm.enable(MOTOR4);

	pwm.set_period(MOTOR1,50);
	pwm.set_period(MOTOR2,50);
	pwm.set_period(MOTOR3,50);
	pwm.set_period(MOTOR4,50);
	
	printf("Enable PWM\n");

	while(true)
	{
		pwm.set_duty_cycle(MOTOR1, SERVO_MAX);
		pwm.set_duty_cycle(MOTOR2, SERVO_MAX);
		pwm.set_duty_cycle(MOTOR3, SERVO_MAX);
		pwm.set_duty_cycle(MOTOR4, SERVO_MAX);
		led.setColor(Colors::Red);
		printf("Servo HIGH\n");
		sleep(1);

		pwm.set_duty_cycle(MOTOR1,SERVO_MIN);
		pwm.set_duty_cycle(MOTOR2,SERVO_MIN);
		pwm.set_duty_cycle(MOTOR3,SERVO_MIN);
		pwm.set_duty_cycle(MOTOR4,SERVO_MIN);
		led.setColor(Colors::Blue);
		printf("Servo LOW\n");
		sleep(1);
	}
	return 1;
}
