#include <unistd.h>
#include "Navio/RCInput.h"
#include "Navio/Util.h"
#include "stdio.h"


int main()
{
	RCInput rcin;

	if(check_apm()) { return 1;}

	rcin.init();

	while(true)
	{
		volatile int rawInput = rcin.read(0);
		float dutyCycle =(float)rawInput/1000;
		printf("%f",dutyCycle);
	}
	return 1;
}

