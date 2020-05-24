#include <iostream>
#include <wiringPiI2C.h>
#include <fstream>
#include <unistd.h>
#include <ctime>

#define DEVICE_ID 0x08

using namespace std;

const int AirValue = 505;   //you need to replace this value with Value_1
const int WaterValue = 278;  //you need to replace this value with Value_2
int intervals = (AirValue - WaterValue)/3;
int soilMoistureValue = 0;

// Se va necesitar como calcular la humedad en la tierra,por 
// lo menos unas 7.62cm abajo de la tierra.
// There will be a need calculate the moisture in the dirt,
// at least 7.62 cm under the surface.
int soildb = false; // Soil Dry Base.
int soildwb = false; // Soild Completely Saturated with water.

void writeToFile(fstream& outfile, int data) {
	time_t utime = time(nullptr);
	outfile.open("data.txt", ios_base::app);
	outfile << data <<"," << utime << endl;
	outfile.close();
}

int main(){
	fstream outfile;
	// setup I2C communication
	int fd = wiringPiI2CSetup(DEVICE_ID);
	if(fd == -1) {
		cout << "Failed to init I2C communication. \n";
		return -1;
	}
	while(true){
		// cout << "I2C communication successfully setup. \n";

		// Send data to arduino
		uint8_t data_to_send = 17;
		wiringPiI2CWrite(fd, data_to_send);
		// cout << "Sent data: " << (int)data_to_send << "\n";
		// Read data from arduino
		int received_data = wiringPiI2CRead(fd);
		writeToFile(outfile, received_data);
		// cout << "Data received: " << received_data << "\n";
		// if (received_data == data_to_send) {
		//	cout << "Success!\n";
		//}
		usleep(4e3);
	}
	return 0;

}
