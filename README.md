HDC1000 Arduino Library
=======================

Here's my Arduino library for the TI HDC1000 temperature and humidity sensor. It should work with the HDC1008 too but I haven't tested it.

More details about the library and my breakout board for the chip on my website http://b.truzzi.me/hdc1000-temperature-and-humidity-sensor-breakout-with-arduino-library/.

### Setup your sensor:
First, declare it:

`HDC1000 mySensor;`

Default address is 0x40 and the DRDYn pin is disabled. You can change your address by declaring your sensor like this:

`HDC1000 mySensor(addr. DRDYn_pin);`

Then, initialize it:

`mySensor.begin();`

Default options are set to enable both temperature and humidity readings, at 14-bit resolution, with the integrated heater on. You can change them by initializing your sensor like this:

`mySensor.begin(mode, resolution, heater);`

"mode" can be _HDC1000_SINGLE_MEASUR_, _HDC1000_BOTH_TEMP_HUMI_ or _HDC1000_RST_.

"resolution" can be _HDC1000_TEMP_HUMI_14BIT_, _HDC1000_TEMP_11BIT_, _HDC1000_HUMI_11BIT_, _HDC1000_HUMI_8BIT_.

"heater" can be _HDC1000_HEAT_ON_ or _HDC1000_HEAT_OFF_.

### Read some values
You can read temperature and humidity by using the following commands:

`double temperature = mySensor.getTemp();` in Celsius degrees.

`double humidity = mySensor.getHumi();` in %

You can also access raw values from the sensor:

`uint16_t temp = mySensor.getRawTemp();`

`uint16_t humi = mySensor.getRawHumi();`

### Check your battery

The following code returns '1' if the battery voltage is <2.8V, '0' otherwise.

`boolean isDead = mySensor.battery();`

### Read the internal registers' configuration:

This returns the 16-bit value of the internal configuration register (0x02): the last 8 bits are always zero and leading zeros are not displayed.

`uint16_t config = mySensor.readConfig();`

Happy making!
