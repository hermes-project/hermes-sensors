#include <iostream>
#include <unistd.h>
#include "Srf02.hpp"
#include <fcntl.h>
#include <stdio.h>
#include <vector>
#include <numeric>

using namespace std;

int main(){

	int Bus_I2C = open("/dev/i2c-2", O_RDWR);

	vector<Srf02> sensors;

	vector<int> values(4, 0);


	Srf02 test1(Bus_I2C, 0x71);
	Srf02 test2(Bus_I2C, 0x72);
	Srf02 test3(Bus_I2C, 0x73);
	Srf02 test4(Bus_I2C, 0x75);

	sensors.push_back(test1);
	sensors.push_back(test2);
	sensors.push_back(test3);
	sensors.push_back(test4);



	while(1){

		for(unsigned int j=0; j<sensors.size(); j++){
			values[j] = (int)sensors[j].get_i2c_register(3);
			usleep(1000);
			sensors[j].writeValue(0x51);
			usleep(200000);
		

			if(values[j]<30 && values[j]!=1){
				cout << "Obstacle a "<< dec << values[j] << " cm devant " << hex << sensors[j].I2CAddress << endl;
			} else if(values[j]==1){
				cout << "SENSOR " << hex << sensors[j].I2CAddress << " UNREACHABLE --> Removed from update list" << endl;
				sensors.erase(sensors.begin()+j);
			}
		}

	
	}

	return 0;
}
