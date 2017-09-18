#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void readFile(fstream &data), vector<string> &dataBuffer);

int main() {
	fstream dataFile;
	vector<string> inputStream;

	for (int i = 0; i <  inputStream.size(); i++)
	{
		cout << inputStream[i]<<endl;
	}

	return 0;
}

void readFile(fstream &data), vector<string> &dataBuffer)
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
