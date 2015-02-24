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

HDC1000::HDC1000(uint8_t address){
	_addr = address;
}

uint8_t HDC1000::begin(uint8_t mode, uint8_t resolution, uint8_t heater){

	Wire.begin();

	uint8_t config = mode|resolution|heater;

	setConfig(config);

	return config;
}

uint16_t HDC1000::readConfig(void){
	uint16_t config = 0;

	setReadRegister(HDC1000_CONFIG);

	return read16(config);
}

void HDC1000::setReadRegister(uint8_t reg){
	Wire.beginTransmission(_addr);
	Wire.write(reg);
	Wire.endTransmission();

	delay(20);
}

void HDC1000::setConfig(uint8_t config){
	Wire.beginTransmission(_addr);
	Wire.write(HDC1000_CONFIG); //accessing the configuration register
	Wire.write(config); //sending the config bits (MSB)
	Wire.write(0x00); //the last 8 bits must be zeroes
	Wire.endTransmission();
}

uint16_t HDC1000::read16(uint16_t dest){
	uint8_t bytes = 2;

	Wire.requestFrom(_addr, bytes);
	if(Wire.available()>=bytes){
		dest = Wire.read()<<8;
		dest += Wire.read();
	}
	return dest;
}

uint16_t HDC1000::getRawTemp(void){
	uint16_t temp = 0;

	setReadRegister(HDC1000_TEMP);

	return read16(temp);
}

uint16_t HDC1000::getRawHumi(void){
	uint16_t humi = 0;

	setReadRegister(HDC1000_HUMI);

	return read16(humi);
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