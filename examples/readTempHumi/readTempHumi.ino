#include <Wire.h>
#include <HDC1000.h>
 
HDC1000 mySensor;
 
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