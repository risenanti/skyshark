#include "PID.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

long millis(void)
{
	FILE *in=fopen("/proc/uptime", "r");
    double retval=0;
    char tmp[256]={0x0};
    if(in!=NULL)
    {
          fgets(tmp, sizeof(tmp), in);
          retval=atof(tmp);
          fclose(in);
    }
    return retval*1000;
}

PID::PID(double* Input, double* Output, double* Setpoint,
        double Kp, double Ki, double Kd, int POn, int ControllerDirection)
{
    myOutput = Output;
    myInput = Input;
    mySetpoint = Setpoint;
    inAuto = false;

    PID::SetOutputLimits(0, 255);				//default output limit corresponds to
												//the arduino pwm limits

    SampleTime = 100;							//default Controller Sample Time is 0.1 seconds

    PID::SetControllerDirection(ControllerDirection);
    PID::SetTunings(Kp, Ki, Kd, POn);

    lastTime = millis()-SampleTime;
}

/*Constructor (...)*********************************************************
 *    To allow backwards compatability for v1.1, or for people that just want
 *    to use Proportional on Error without explicitly saying so
 ***************************************************************************/

PID::PID(double* Input, double* Output, double* Setpoint,
        double Kp, double Ki, double Kd, int ControllerDirection)
    :PID::PID(Input, Output, Setpoint, Kp, Ki, Kd, P_ON_E, ControllerDirection)
{

}
