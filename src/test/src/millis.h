/*KEITH CONLEY
**USM
**FALL 2018
*/

#ifndef millis_h
#define millis_h

void timer_handler (int signum);
int createMillisTimer(void);
long long int millis(void);
void delay(int x);

namespace millTim{

	static long long int count;
	static bool millisFlag = false;
}
#endif
