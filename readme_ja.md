# NetLCD

ネットワーク経由利用可能な320 x 240 dotの小型カラー液晶ディスプレーのためのESP8266-Arduino sketch

<img src="https://github.com/h-nari/NetLCD/blob/master/img/160819a3.jpg?raw=true">

## Description

ESP-WROOM-02はWiFi機能を有するコンピュータモジュールで[esp8266/Arduino](https://github.com/esp8266/Arduino "esp8266/Arduino: ESP8266 core for Arduino")でプログラムを組むことができ、多くのライブラリが提供されています。ILI9341コントローラ使用の小型カラー液晶もライブラリが提供されています。

このリポジトリは、ESP-WROOM-02とILI9341搭載ディスプレイを組み合わせたハードウェアをネットワーク経由で操作可能なディスプレイにするためのESP8266-Arduino用のスケッチ(プログラム)を提供します。このスケッチは、WebServerとして動作し、文字、線、画像等の表示が可能です。

文字、線等の表示は簡単でブラウザから人手で行うことも可能ですが、画像の表示は若干複雑なので、Pythonのパッケージも用意しました。これを使用するとPythonのPILライブラリの画像を1アクションで表示できます。

### 他のドキュメント

- [NetLCD/install_ja.md](https://github.com/h-nari/NetLCD/blob/master/sketch_NetLCD/install.md "NetLCD/install_ja.md at master · h-nari/NetLCD"): sketch_netLcd.ino のインストール方法
- [NetLCD/usage_ja.md](https://github.com/h-nari/NetLCD/blob/master/sketch_NetLCD/usage_ja.md "NetLCD/usage.md at master · h-nari/NetLCD"): sketch_netLcd.inoの使い方、 アクション、パラメータについて
- [NetLCD/readme_ja.md](https://github.com/h-nari/NetLCD/blob/master/python/readme.md "NetLCD/readme_ja.md at master · h-nari/NetLCD"): netLcd.py , python libraryについて.

## Demo

pythonディレクトリにある drawTest.pyをPC側で動作させ、ネット経由で描画させています。

- [youtube : demo drawTest.py](https://youtu.be/M9U3qatbHAc,"drawTest.py")

## Requirement - Hardware

- ILI9341をコントローラとするディスプレーとESP-WROOM-02を有する装置

## Author

[h-nari](https://github.com/h-nari "h-nari (Hiroshi Narimatsu)")
