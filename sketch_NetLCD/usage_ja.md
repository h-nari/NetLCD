# 使い方

## URL

以下の形式のURLにアクセスすることで文字、直線等を描画できます。
パラメータの設定が行われた後actionで指定された描画を行います。
但し、imageアクションだけは、パラメータの指定を無視します。

~~~
http://ip_addr/action?param1=value1&param2=value2&...
~~~

## actionとパラメータ

| action | 動作 |影響を受けるparameter |
|--------|------|-------|
| circle| 円 | rotation, x, y, r, color, fill|
| clear | 画面消去 | bg |
| image    | イメージ描画  |rotation|
| line | 直線描画 | rotation,x0, y0, x1, y1, color |
| print  | 文字描画| rotation, text, tx, ty, color, bg, text_size, obscure,clear|
| pset | 点描画 | rotation,x, y, color |
| rect | 長方形描画 | rotation,x, y, w, h, color, fill |
| roundrect | 各丸長方形| rotation, x, y, w, h, r, color, fill|
| set     | パラメータの設定|   |

## パラメータ

パラメータのリストを以下に示します。
ほとんどのパラメータの値は保持され、
以降のアクションでも使用可能です。
保存されないのは、文字の位置を示すtx,tyと
描画前のクリア動作を示すclearパラメータだけです。

|name|type|意味|初期値|
|----|------|------|-------|
|bg   | color |背景色| #000000|
|clear| boolean |描画前に画面クリア|false|
|color| color |描画色| #ffffff| 
|fill | boolean | 塗潰すか | false|
|h  | integer | 長方形の高さ | 50 |
|obscure | boolean | 背景を塗潰すか| false| 
|r  | integer | 円、各丸の半径| 5 |
|rotation|integer|描画方向|3|
|text_size| integer | 文字描画倍率 | 2|
|text|string|描画文字列|''|
|tx  |integer | 文字描画x座標| 0 | 
|ty  |integer | 文字描画y座標| 0 | 
|w  | integer | 長方形の幅 | 50 | 
|x  | integer | 図形描画x座標 | 0 | 
|x0 | integer | 図形描画x座標 | 319 | 
|x1 | integer | 図形描画x座標 | 0 | 
|y  | integer | 図形描画x座標 | 0 | 
|y0 | integer | 図形描画y座標 |239|
|y1 | integer | 図形描画y座標 |0 | 
