# netLcd.py

sketch_netLcd.inoと通信をするためのPythonモジュール。  
文字列、図形、ビットマップの描画機能を有する。

## 概要

sketch_netLcd.inoが動作するESP8266-ArduinoマシンではWebサーバが動作しており、
ブラウザから簡単に表示を制御できます。 しかし、これをプログラミング言語からアクセスできると更に便利です。
ほとんどのプログラミング言語はWebアクセスの機能あるいはライブラリを有していますので
プログラムで表示をコントロールすることが可能です。

netLcd.pyはPython用の描画ライブラリです。
以下の機能があります。

- 文字、点、直線、長方形、各丸長方形、円の描画
- PIL(Pillow)ライブラリのImageオブジェクトの描画

## 対応するPythonのversion

netLcd.pyはPython3, Python2の両方に対応しています。  
日本語を扱う場合、Python2ではうまくいかないかもしれません。

## 必要なライブラリ

netLcd.pyではPython標準のライブラリ以外に Pillow と requests ライブラリを使用しています。
pip等でインストールしてください。

- [Pillow — Pillow (PIL Fork) 3.3.1 documentation](https://pillow.readthedocs.io/en/3.3.x/# "Pillow — Pillow (PIL Fork) 3.3.1 documentation")
- [Requests: 人間のためのHTTP — requests-docs-ja 1.0.4 documentation](http://requests-docs-ja.readthedocs.io/en/latest/# "Requests: 人間のためのHTTP — requests-docs-ja 1.0.4 documentation")

## インストール

netLcd.pyを適当なディレクトリに置き使用してください。

## 使用方法

netLcd.pyは短い簡単なプログラムですので、ソースコードとサンプルプログラムを見てください。
使用できるパラメータについては、sketch_netLcd側の説明を見てください


## サンプルプログラム

以下のサンプルプログラムを同梱しています。  
引数として sketch_netLcd.inoが動作しているボードのIPアドレスを与えてください

- clock.py : 時計
- drawTest.py : 描画機能のデモ
- imageDisp.py : 画像ファイルを表示します。複数指定可能です。
- kanjiTest.py : PIL側で文字を描画し、転送するデモ。Python2だと日本語表示がうまくいかないかもしれません。

## 画像ファイル img_miku_web.jpgのライセンス

'Hatsune Miku / Crypton Future Media inc. / CC BY-NC'