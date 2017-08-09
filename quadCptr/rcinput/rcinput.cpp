#include <unistd.h>
#include "Navio/RCInput.h"
#include "Navio/Util.h"
#include "stdio.h"

float mapRanges(float x, float in_min, float in_max, float out_min, float out_max);
float processCH1(float ch1);

int main()
{
	RCInput rcin;

	if(check_apm()) { return 1;}

	rcin.init();

	while(true)
	{
		volatile int rawInput1 = rcin.read(0);
		volatile int rawInput2 = rcin.read(1);
		volatile int rawInput3 = rcin.read(2);
		volatile int rawInput4 = rcin.read(3);

		float dutyCycle =(float)rawInput1/1000;

		if(dutyCycle>1.75) {dutyCycle=1.75;}

		if (dutyCycle<1.0) {dutyCycle=1.0;}

		printf("rc0: %f \n",dutyCycle);

		float dutyCycle1 =(float)rawInput2/1000;
		dutyCycle1 = processCH1(dutyCycle1);

		float dutyCycle2 =(float)rawInput3/1000;
		printf("rc2: %f \n", dutyCycle2);

		float dutyCycle3 =(float)rawInput4/1000;
		printf("rc3: %f \n\n", dutyCycle3);
		sleep(1);
	}
	return 1;
}

float mapRanges(float x, float in_min, float in_max, float out_min, float out_max)
{
 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float processCH1(float ch1)
{
	float dutyCycle1;
	if(ch1 > 1.55)
	{
	dutyCycle1 = ch1, 1.5, 2, 0, 0.3;
	printf("\nrc1: = %f R \n", dutyCycle1);
	return dutyCycle1;
	}
	if(ch1 < 1.45) 
	{
	ch1 = 2.5-ch1;
	dutyCycle1 = ch1, 1.0, 1.5, 0, 0.3;
	printf("\nrc1: = %f L \n", dutyCycle1);
	return dutyCycle1;
	}
return ch1;
}
