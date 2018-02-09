/*Copyright Jackal Robotics LLC*/
/*Keith Conley 2017*/

#ifndef pid_h
#define pid_h

class PID
{
	public:
	
	PID();
	
	void Compute(void);
	void SetTunings(double Kp, double Ki, double Kd);
	void setImax(double imax);
	void resetI(void);
	double getPID(double error);
	
	private:
	unsigned long lastTime;
	double Input, Output, Setpoint;
	double errSum; //used as accumulated error for kiTerm 
	double lastErr;
	double kp, ki, kd;
	double kpTerm, kiTerm, kdTerm; //save individual output pieces
	double iMax;
};
#endif


/*Copyright Jackal Robotics LLC*/
/*Keith Conley 2017*/
