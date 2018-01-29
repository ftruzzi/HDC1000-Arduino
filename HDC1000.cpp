/***********************

This library was written for the Texas Instruments 
HDC1000 temperature and humidity sensor. 
It should work for the HDC1008 too.
More info on my website: http://truzzi.me
Written by Francesco Truzzi.
Released under GNU GPL v2.0 license.

*************************/ 

#include "HDC1000.h"
#include "Wire.h"
#include <util/delay.h>

HDC1000::HDC1000(uint8_t address, int drdyn_pin){
	_addr = address;
	_drdyn_pin = drdyn_pin;

	if(_drdyn_pin > -1) pinMode(_drdyn_pin, INPUT);
}

uint8_t HDC1000::begin(uint8_t mode, uint8_t resolution, uint8_t heater){
	Wire.begin();

	uint8_t config = mode|resolution|heater;

	setConfig(config);

	return config;
}

uint16_t HDC1000::readConfig(void){
	setReadRegister(HDC1000_CONFIG);

	return read16();
}

void HDC1000::setReadRegister(uint8_t reg){
	Wire.beginTransmission(_addr);
	Wire.write(reg);
	Wire.endTransmission();

	if(_drdyn_pin > -1) while(digitalRead(_drdyn_pin)==HIGH); //using DRDYn pin
	else delay(20);	//using 20ms delay instead
}

void HDC1000::setConfig(uint8_t config){
	Wire.beginTransmission(_addr);
	Wire.write(HDC1000_CONFIG); //accessing the configuration register
	Wire.write(config); //sending the config bits (MSB)
	Wire.write(0x00); //the last 8 bits must be zeroes
	Wire.endTransmission();
}

uint16_t HDC1000::read16(){
	uint8_t bytes = 2;
	uint16_t dest;

	Wire.requestFrom(_addr, bytes);
	if(Wire.available()>=bytes){
		dest = Wire.read()<<8;
		dest += Wire.read();
	}
	return dest;
}

uint16_t HDC1000::getRawTemp(void){
	setReadRegister(HDC1000_TEMP);

	return read16();
}

uint16_t HDC1000::getRawHumi(void){
	setReadRegister(HDC1000_HUMI);

	return read16();
}

double HDC1000::getTemp(void){
	double temp = getRawTemp();

	return temp/65536.0*165.0-40.0;
}

double HDC1000::getHumi(void){
	double humi = getRawHumi();

	return humi/65536.0*100.0;
}

boolean HDC1000::battery(){
	return(bitRead(readConfig(), 11));
}
