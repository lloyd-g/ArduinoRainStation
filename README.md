# ArduinoRainStation
using low cost transducers make a rain prediction

BMP180 Digital Barometric Pressure Sensor
got a module off ebay but so far testing with Arduino libraries the only one that seems to work reliably
is 

https://github.com/sparkfun/BMP180_Breakout_Arduino_Library

So will add some test code.
the Quick start guide was very helpfull

https://learn.sparkfun.com/tutorials/bmp180-barometric-pressure-sensor-hookup-


Noticed that Weather Observations are reported at Sea Level. This library has a correction function for this seaLevel(P,A). This takes absolute pressure (P) in hPa, and the station’s current altitude (A) in meters, and removes the effects of the altitude from the pressure but you need to know your station altitude to start with. 

quick google gave https://www.freemaptools.com/elevation-finder.htm



DHT11 Temp & Humidity sensor

maybe store data to SDCard or eeprom on TinyRTC V1.1?

There are 2 vesions of LCD test as I started working online and forgot sketch name and folder name have to be same. not sure how to remove it?

There  may be other things like this as I'm new to git. Started to on svn at work and google code but getting the hang of it.
