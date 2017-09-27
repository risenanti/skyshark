#ifndef millis_h
#define millis_h

void timer_handler (int signum);
void createMillisTimer(void);
long long int millis(void);
void delay(int x);

namespace millTim{

	static long long int count;
}



#endif
