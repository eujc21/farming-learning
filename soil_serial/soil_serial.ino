#include <Wire.h>
#include <math.h>
#define SLAVE_ADDRESS 0x08

const int AirValue = 505;   //you need to replace this value with Value_1
const int WaterValue = 278;  //you need to replace this value with Value_2
int intervals = (AirValue - WaterValue)/3;
int soilMoistureValue = 0;

byte data_to_echo = 0;

using namespace std;

void setup(){
  Wire.begin(SLAVE_ADDRESS);

  Wire.onReceive(recieveData);
  Wire.onRequest(sendData);
}


void loop() {
//Serial.begin(9600); // open serial port, set the baud rate as 9600 bps
//Serial.println(data_to_echo);
//soilMoistureValue = analogRead(A0);  //put Sensor insert into soil
//  
//  if(soilMoistureValue > WaterValue && soilMoistureValue < (WaterValue + intervals))
//  {
//    Serial.println("Very Wet");
//  }
//  else if(soilMoistureValue > (WaterValue + intervals) && soilMoistureValue < (AirValue - intervals))
//  {
//    Serial.println("Wet");
//  }
//  else if(soilMoistureValue < AirValue && soilMoistureValue > (AirValue - intervals))
//  {
//    Serial.println("Dry");
//  }
  delay(100);
}

void recieveData(int bytecount) {
  Serial.begin(9600); // open serial port, set the baud rate as 9600 bps
  Serial.println(bytecount);
  Serial.println(Wire.read());
  for  (int i=0; i < bytecount; i++){
    data_to_echo = Wire.read(); 
  }  
}

void sendData() {
  Wire.write(analogRead(A0));
}
