#include <Wire.h>
#include <HDC1000.h>
 
HDC1000 mySensor;
//HDC1000 mySensor(0x40, 2) <-- DRDYn enabled and connected to Arduino pin 2 (allows for faster measurements).
 
void setup(){
	Serial.begin(9600);
	mySensor.begin();
}
 
void loop(){
    Serial.print("Temperature: ");
    Serial.print(mySensor.getTemp()); 
    Serial.print("C, Humidity: ");     
    Serial.print(mySensor.getHumi());
    Serial.println("%");
	delay(1000);
}
