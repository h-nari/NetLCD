# NetLCD

Programs for ESP8266 with 320 x 240 color LCD Display
can be used over network.

<img src="https://github.com/h-nari/NetLCD/blob/master/img/160819a3.jpg?raw=true" width="480">

## Description

ESP-WROOM-02 is computer module that has WiFi abilities and can be programmed whith [esp8266/Arduino](https://github.com/esp8266/Arduino "esp8266/Arduino: ESP8266 core for Arduino") and many libraries are provided for it. Libraries for color TFT LCD module with ILI9341 controller are also provieded.

This repository contains a ESP8266-Arduino sketch , python library and sample programs. The Sketch make a ESP-WROOM-02 with ILI9341 display network operatable.
This sketch run as a web server, can draw text, line, shapes and image.

Python library provides a class, that can draw text, shapes and image easily

### Other document

- [sketch_NetLCD/install.md](https://github.com/h-nari/NetLCD/blob/master/sketch_NetLCD/install.md "sketch_NetLCD/install.md at master · h-nari/NetLCD"): how to install sketch_netLcd.ino
- [sketch_NetLCD/usage.md](https://github.com/h-nari/NetLCD/blob/master/sketch_NetLCD/usage.md "sketch_NetLCD/usage.md at master · h-nari/NetLCD"): how to use sketch_netLcd.ino, actions and parameters.
- [python/readme.md](https://github.com/h-nari/NetLCD/blob/master/python/readme.md "python/readme.md at master · h-nari/NetLCD"): how to install netLcd.py , python library.

## Demo

The follow video show drawTest.py in python directory, that run on PC and draw picture over network.

- [youtube : demo drawTest.py](https://youtu.be/M9U3qatbHAc "drawTest.py")

## Requirement - Hardware

- ESP8266 and LCD display with ILI9341 controller
 - [HSES-LCD24](https://www.switch-science.com/catalog/2829/ "HSES-LCD24 - スイッチサイエンス")

## reqirement - Libraries

- Adafruit_GFX
- Adafruit_ILI9341 (ver 1.0.2)
- [Humblesoft_ILI9341](https://github.com/h-nari/Humblesoft_ILI9341 "h-nari/Humblesoft_ILI9341: add some functions to Adaruit_ILI9341")

## Author

[h-nari](https://github.com/h-nari "h-nari (Hiroshi Narimatsu)")
