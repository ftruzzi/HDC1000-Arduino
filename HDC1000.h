/***********************

This library was written for the Texas Instruments 
HDC1000 temperature and humidity sensor. 
It should work for the HDC1008 too.
More info on my website: http://truzzi.me
Written by Francesco Truzzi.
Released under GNU GPL v2.0 license.

*************************/ 

#ifndef HDC1000_H
#define HDC1000_H

#include <inttypes.h>

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#define HDC1000_ADDR				0x40

#define HDC1000_TEMP				0x00
#define HDC1000_HUMI				0x01
#define	HDC1000_CONFIG				0x02

#define HDC1000_SERID_1				0xFB
#define HDC1000_SERID_2				0xFC
#define HDC1000_SERID_3				0xFD
#define HDC1000_MFID				0xFE
#define HDC1000_DEVID				0xFF

#define HDC1000_RST					0x80
#define	HDC1000_HEAT_ON				0x20
#define	HDC1000_HEAT_OFF			0x00
#define	HDC1000_BOTH_TEMP_HUMI		0x10
#define	HDC1000_SINGLE_MEASUR		0x00
#define	HDC1000_TEMP_HUMI_14BIT		0x00
#define	HDC1000_TEMP_11BIT			0x40
#define HDC1000_HUMI_11BIT			0x01
#define	HDC1000_HUMI_8BIT			0x02

class HDC1000{
	public: 
		HDC1000(uint8_t address = HDC1000_ADDR);

		uint8_t begin(uint8_t mode = HDC1000_BOTH_TEMP_HUMI, uint8_t resolution = HDC1000_TEMP_HUMI_14BIT, uint8_t heater = HDC1000_HEAT_ON);

		boolean battery();

		uint16_t getRawTemp(void);
		uint16_t getRawHumi(void);

		double getTemp(void);
		double getHumi(void);

		uint16_t readConfig(void);

	private:
  		uint8_t _addr;
  		uint16_t read16(uint16_t dest);
  		void setReadRegister(uint8_t reg);
  		void setConfig(uint8_t config);
};

#endif