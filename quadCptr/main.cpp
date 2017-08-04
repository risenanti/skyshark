#include <unistd.h>
#include "Navio/RGBled.h"
#include "Navio/PWM.h"
#include "Navio/Util.h"
#include <stdio.h>

#define PWM_OUTPUT 0
#define SERVO_MIN 1.250 /*MS*/
#define SERVO_MAX 1.750 /*MS*/

int main()
{
	RGBled led;
	PWM pwm;

	if(check_apm()) { return 1;}

	if (!led.initialize()) return EXIT_FAILURE;
	if (!pwm.init(PWM_OUTPUT)) 
	{
		fprintf(stderr,"OUTPUT ENABLE NOT SET. Are you root?\n");
		return 0;
	}

	led.setColor(Colors::Yellow);
	pwm.enable(PWM_OUTPUT);
	pwm.set_period(PWM_OUTPUT,50);
	
	int i = 5;

	while(i!=0)
	{
		pwm.set_duty_cycle(PWM_OUTPUT, SERVO_MAX);
		led.setColor(Colors::Red);
		printf("Servo HIGH\n");
		sleep(10);
		
		pwm.set_duty_cycle(PWM_OUTPUT,SERVO_MIN);
		led.setColor(Colors::Blue);
		printf("Servo LOW\n");
		sleep(10);
		i--;
	}
	printf("HELLO WORLD\n");
	return 1;
}
