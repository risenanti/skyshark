#include "pid.h"
#include "millis.h"



double PID::getPID(double error)
{
	double output;
	unsigned long now = millis();
	double timeChange = (double)(now-lastTime);
	
	kpTerm = kp*error;
	
	/*Compute and bound integral*/
	errSum += (error*timeChange);
	kiTerm = errSum * ki;
	if (kiTerm>iMax)
	{
		kiTerm = iMax;
	}
	else if (kiTerm < -iMax)
	{
		kiTerm = -iMax;
	}
	
	kdTerm = (error - lastErr) / timeChange;
	
	output = kpTerm+kiTerm+kdTerm;
	
	lastErr = error;
	lastTime = now;
	
	return output;
}

PID::PID()
{
	kp =0; ki =0; kd = 0;
}

void PID::Compute(void)
{
   /*How long since we last calculated*/
   unsigned long now = millis();
   double timeChange = (double)(now - lastTime);
  
   /*Compute all the working error variables*/
   double error = Setpoint - Input;
   errSum += (error * timeChange);
   double dErr = (error - lastErr) / timeChange;
  
   /*Compute PID Output*/
   Output = kp * error + ki * errSum + kd * dErr;
  
   /*Remember some variables for next time*/
   lastErr = error;
   lastTime = now;
}
  
void PID::SetTunings(double Kp, double Ki, double Kd)
{
   kp = Kp;
   ki = Ki;
   kd = Kd;
}

void PID::resetI(void)
{
	kiTerm = 0;
	errSum = 0;
}

void PID::setImax(double imax)
{
	iMax = imax;
}
