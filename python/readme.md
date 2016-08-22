# netLcd.py

A Python module for communicate with sketch_netLcd.ino,
can draw text, shapes, bitmap.

## abstract

A web server is running on ESP8266-Arduino machine that run a program compiled sketch_netLcd.ino, you can draw on it easily with browser.

netLcd.py is python library, and provide following functions.

- draw text, point, line, rectangle, round rectangle, circle
- draw Image object of PIL(Pillow) library

## Python version

netLcd.py can be used with Python version 3 and version 2.
but when you use multi-byte charactors, python version 2 may not
be able to handle them.

## required library 

netLcd.py require "Pillow" and "requests" library.

- [Pillow — Pillow (PIL Fork) 3.3.1 documentation](https://pillow.readthedocs.io/en/3.3.x/# "Pillow — Pillow (PIL Fork) 3.3.1 documentation")
- [Requests: HTTP for Humans — Requests 2.11.1 documentation](http://docs.python-requests.org/en/master/ "Requests: HTTP for Humans — Requests 2.11.1 documentation")

## Install

put netLcd.py in appropreate directory.

## Usage

netLcd.py is short program. So read it and sample programs.
if you want to know about parameters, read ../sketch_netLcd/usage.md

## sample programs

Sample programs are included.
Usages will be showed when invoking with no arguments. 

- clock.py : clock
- drawTest.py : demo of drawing functions
- imageDisp.py : display image files 
- kanjiTest.py : demo of drawing text on PIL side

## License of image file img_miku_web.jpg

  'Hatsune Miku / Crypton Future Media inc. / CC BY-NC'