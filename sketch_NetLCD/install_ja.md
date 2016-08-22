# インストール

## Arduino

Arduinoがインストールされていなければ、
Arduino Homepageからダウンロードし、インストールしてください。

- [Arduino Homepage](https://www.arduino.cc/en/main/software "Arduino - Software")

## ESP8266 Arduino

ESP8266 Arduinoがインストールされていなければ、インストールしてください。


- [ESP8266 Arduinoのインストール](http://www.humblesoft.com/wiki/?ESP8266%20Arduino%E3%81%AE%E3%82%A4%E3%83%B3%E3%82%B9%E3%83%88%E3%83%BC%E3%83%AB "ESP8266 Arduinoのインストール")
- [esp8266/Arduino: ESP8266 core for Arduino](https://github.com/esp8266/Arduino "esp8266/Arduino: ESP8266 core for Arduino")

## Arduinoのライブラリ

sketch_NetLCD.inoをコンパイルするには、Adafruit_GFXとAdafruit_ILI9341の２つのライブラリが必要です。
Arduino-IDEのライブラリマネージャでインストールされるAdafruit_ILI9341は、
バージョン1.01で動作しませんので、githubから1.02をインストールしてください。
zipファイルでダウンロードし、
IDEの「スケッチ/ライブラリをインクルード/zip形式のライブラリをインストール」を
行うと、簡単にインストールできます。 Adafruit_GFXはどちらでインストールしても問題ありません。

- [adafruit/Adafruit_ILI9341: Library for Adafruit ILI9341 displays](https://github.com/adafruit/Adafruit_ILI9341 "adafruit/Adafruit_ILI9341: Library for Adafruit ILI9341 displays")
- [adafruit/Adafruit-GFX-Library: Adafruit GFX graphics core library, this is the 'core' class that all our other graphics libraries derive from](https://github.com/adafruit/Adafruit-GFX-Library "adafruit/Adafruit-GFX-Library: Adafruit GFX graphics core library, this is the 'core' class that all our other graphics libraries derive from")

## WiFiの設定

conf.h-sampleをconf.hにコピーし、お使いのWiFiのSSIDとパスワードを設定してください。

## ESP8266とILI9341の接続の確認

このスケッチは、
[HSES-LCD24](http://www.humblesoft.com/products/HSES-LCD24/ "HSES-LCD24/ 製品情報/ ハンブルソフト")用に作られており、以下の接続を前提としております。

|信号|ピン|
|----|----|
|CS  |IO2 |
|DC  |IO15|
|Reset|未接続|
|SCK |IO14|
|MISO|IO12|
|MOSI|IO13|

接続が異なる場合、 sketch_NetLCD.inoの先頭にある以下の部分のコメントを外して
修正してください。

~~~
// #define CS_PIN	2
// #define DC_PIN	13
// #define RST_PIN	-1
// HSES_LCD24 tft = HSES_LCD24(CS_PIN, DC_PIN, RST_PIN);

HSES_LCD24 tft = HSES_LCD24();	// default connection CS-IO2,DC-IO13,RST-NC
~~~

## コンパイル

以上の準備ができたら、Arduino-IDEでコンパイルしプログラムを書き込みます。

## 動作

動作すると、液晶に以下のような、表示が現れます。

<img src="https://github.com/h-nari/NetLCD/blob/master/img/160819a2.jpg?raw=true">

シリアルモニターを baudrate 115200 で開くと、以下のように表示されるはずです。  
但し ssid名とIPアドレスは、お使いの環境によって変化します。

<img src="https://github.com/h-nari/NetLCD/blob/master/img/sc160819a1.png?raw=true">

あとは、ブラウザでアクセスするだけで表示できます。

~~~
http://192.168.0.101/print?text=Hello&clear=1&text_size=3&tx=0&ty=16
~~~

にアクセスすると、次のように表示されます。

<img src="https://github.com/h-nari/NetLCD/blob/master/img/160810a3.jpg?raw=true">
