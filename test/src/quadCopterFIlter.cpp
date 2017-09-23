#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <stdexcept>
#include "Kalman.h"

using namespace std;

void readDataFile(fstream &data, vector<string> &dataBuffer);
void dataToDoub(vector<string> &dataBuffer, vector<double> &accelData, vector<int> &time);

#define NOISE 0.2100

int main() {
	vector<string> dataBuffer;
	vector<double> accelData;
	vector<int>    time;
	vector<double> filteredValue;
	fstream data;

	readDataFile(data, dataBuffer);
	dataToDoub(dataBuffer, accelData, time);

	Kalman myFilter(0.0001,NOISE,1023,0); //suggested initial values for high noise filtering

	for (int i = 0; i < accelData.size(); i++)
	{
		filteredValue.push_back(myFilter.getFilteredValue(accelData[i]));
	}

	/*Print out acceleration data*/
	data.open("dataOut.txt", fstream::out);
	for (int i = 0; i <  filteredValue.size(); i++)
	{
		string buff;
		buff+="TIME=";
		buff+=to_string(time[i]);
		buff+="  accelMeasurement=";
		buff+=to_string(accelData[i]);
		buff+=" filteredAccelMeasurement=";
		buff+=to_string(filteredValue[i]);
		data <<buff;
		data<<endl;
		//cout<<buff<<endl;
	}
	data.close();
	/*end printing acceleration*/

	vector<double> velocity;
	vector<double> displacement;
	double Vh;
	double TIMESTEP;
	double x=0.00;

	for (int i = 0; i < filteredValue.size(); i++)
	{
		TIMESTEP = 0.000001*time[1];
		double veloc = Vh+((filteredValue[i]-9.857)*TIMESTEP);
		Vh=veloc;
		velocity.push_back(veloc);

		double Xh = x + ((double)0.5*((Vh+velocity[i]) * TIMESTEP));
		x = Xh;
		displacement.push_back(Xh);
		cout << displacement[i]<<endl;
	}



	//Xhat[i] = X+((double)0.5*(V+Vhat[i])*(double)TIMESTEP);
	//X=Xhat[i];

	return 0;
}

void dataToDoub(vector<string> &dataBuffer, vector<double> &accelData, vector<int> &time)
{
	string line;

	for (int i = 1; i <  dataBuffer.size(); i++)
		{
			line = dataBuffer[i];
			string lineParse;
			string timeString;

			for (int z = 0; z!= line.find(" "); z++)
			{
				if (z>5) break;
				try {timeString+=line.at(z);}
				catch (const std::out_of_range& oor) {cout<<"catch: " << z <<endl;}
			}

			int timInt = atoi(timeString.c_str());
			time.push_back(timInt);

			int pos = line.find("AZ:");


			for(int j = 3; j < 9; j++)
			{
				if((pos+j) < line.size())
				{
						lineParse+=line.at(pos+j);
				}

			}
				double tempData = atof(lineParse.c_str());
				accelData.push_back(tempData);
		}
		dataBuffer.clear();
}

void readDataFile(fstream &data, vector<string> &dataBuffer)
{
	string line;
	data.open("accelData.txt", fstream::in);
	while(1)
		{
			if (data.eof()) {break;}
			getline(data,line);
			dataBuffer.push_back(line);
		}
		data.close();
}
