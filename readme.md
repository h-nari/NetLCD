# NetLCD

Programs for ESP8266 with 320 x 240 color LCD Display
can be used over network.

<div align="center">
<img src="https://github.com/h-nari/NetLCD/blob/master/img/160819a3.jpg?raw=true"></div>

## Description

ESP-WROOM-02 is computer module that has WiFi abilities and can be programmed whith [esp8266/Arduino](https://github.com/esp8266/Arduino "esp8266/Arduino: ESP8266 core for Arduino") and many libraries are provided for it. Libraries for color TFT LCD module with ILI9341 controller are also provieded.

This repository contains a ESP8266-Arduino sketch , python library and sample programs. The Sketch make a ESP-WROOM-02 with ILI9341 display network operatable. 
This sketch run as a web server, can draw text, line, shapes and image.

Python library provides a class, that can draw text, shapes and image easily

### Other document

- [NetLCD/install.md](https://github.com/h-nari/NetLCD/blob/master/sketch_NetLCD/install.md "NetLCD/install.md at master · h-nari/NetLCD"): how to install sketch_netLcd.ino 
- [NetLCD/usage.md](https://github.com/h-nari/NetLCD/blob/master/sketch_NetLCD/usage.md "NetLCD/usage.md at master · h-nari/NetLCD"): how to use sketch_netLcd.ino, actions and parameters.
- [NetLCD/readme.md](https://github.com/h-nari/NetLCD/blob/master/python/readme.md "NetLCD/readme.md at master · h-nari/NetLCD"): how to install netLcd.py , python library.

## Demo

The follow video show drawTest.py in python directory, that run on PC and draw picture over network.

<div align="center">
<iframe width="480" height="360" src="https://www.youtube.com/embed/M9U3qatbHAc" frameborder="0"  allowfullscreen></iframe>
</div>

## Requirement - Hardware

- ESP8266 and LCD display with ILI9341 controller

## Author

[h-nari](https://github.com/h-nari "h-nari (Hiroshi Narimatsu)")
