/*KEITH CONLEY
**USM
**FALL 2018
*/


#include "millis.h"
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

void timer_handler (int signum)
{
	millTim::count++;
}

void createMillisTimer(void)
{
	 struct sigaction sa;
	 struct itimerval timer;

	 /* Install timer_handler as the signal handler for SIGVTALRM. */
	 memset (&sa, 0, sizeof (sa));
	 sa.sa_handler = &timer_handler;
	 sigaction (SIGVTALRM, &sa, NULL);

	 /* Configure the timer to expire after 1 msec... */
	 timer.it_value.tv_sec = 0;
	 timer.it_value.tv_usec = 1000;
	 /* ... and every 250 msec after that. */
	 timer.it_interval.tv_sec = 0;
	 timer.it_interval.tv_usec = 1000;
	 /* Start a virtual timer. It counts down whenever this process is
	   executing. */
	 setitimer (ITIMER_VIRTUAL, &timer, NULL);
}

long long int millis(void)
{
	return millTim::count;
}

void delay(int x)
{
	long long int startTime = 0;
	startTime = millis();
	while(1)
	{
		long long int endTime = millis();

		if(endTime-startTime>x)
		{
			//printf("break\n");
			break;
		}
	}
}
