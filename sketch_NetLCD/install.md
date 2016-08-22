# Install

## Arduino

If Arduino is not installed, download and install it.

- [Arduino Homepage](https://www.arduino.cc/en/main/software "Arduino - Software")

## esp8266 Arduino

If esp8266 Arduino is not installed, install it.

- [esp8266/Arduino: ESP8266 core for Arduino](https://github.com/esp8266/Arduino "esp8266/Arduino: ESP8266 core for Arduino")

## Arduino libraries

sketch_NetLCD.ino requires 2 libraries, Adafruit_GFX and Adafruit_ILI9341.
Adafruit_ILI9341 installed by Library Manager of Arduino-IDE is version 1.01,
cannot be compiled with esp8266 Arduino, so down load zip file of
version 1.02 from GitHUB, and install with 
[import a .zip Library](https://www.arduino.cc/en/Guide/Libraries#toc4 "Arduino - Libraries")

Adafruit_GFX can be installed with both method.

- [adafruit/Adafruit_ILI9341: Library for Adafruit ILI9341 displays](https://github.com/adafruit/Adafruit_ILI9341 "adafruit/Adafruit_ILI9341: Library for Adafruit ILI9341 displays")
- [adafruit/Adafruit-GFX-Library: Adafruit GFX graphics core library, this is the 'core' class that all our other graphics libraries derive from](https://github.com/adafruit/Adafruit-GFX-Library "adafruit/Adafruit-GFX-Library: Adafruit GFX graphics core library, this is the 'core' class that all our other graphics libraries derive from")

## WiFi setting 

copy conf.h-sample to conf.h, and edit conf.h to set your WiFi SSID
and password.

## confirm connection ESP8266 with ILI9341

This sketch is written for 
[HSES-LCD24](http://www.humblesoft.com/products/HSES-LCD24/),
and use connection show bellow.

|Signal|Pin|
|----|----|
|CS  |IO2 |
|DC  |IO15|
|Reset|No Connection|
|SCK |IO14|
|MISO|IO12|
|MOSI|IO13|

If connection is diffrent,
comment out these lines show below in
sketch_NetLCD.ino begining part,
and modify it.

~~~
// #define CS_PIN	2
// #define DC_PIN	13
// #define RST_PIN	-1
// HSES_LCD24 tft = HSES_LCD24(CS_PIN, DC_PIN, RST_PIN);

HSES_LCD24 tft = HSES_LCD24();	// default connection CS-IO2,DC-IO13,RST-NC
~~~

## Compile

Compile sketch with Arduino-IDE and download.

## Running sketch

After sketch run, following messeses will be displayed.  
(ip address will be diffrent)

<img src="https://github.com/h-nari/NetLCD/blob/master/img/160819a2.jpg?raw=true">

Following messeses will be displayed on serial monitor,
baudrate is 115200.
Ssid and ip address will be changed by networks.

<img src="https://github.com/h-nari/NetLCD/blob/master/img/sc160819a1.png?raw=true">

Access following URL (change IP address), 

~~~
http://192.168.0.101/print?text=Hello&clear=1&text_size=3&tx=0&ty=16
~~~

'Hello' will be displayed.

<img src="https://github.com/h-nari/NetLCD/blob/master/img/160810a3.jpg?raw=true">
