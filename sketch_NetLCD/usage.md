## URL

You can draw text and shapes by accessing following format URL.
After parameter settings, drawing specfied by action is performed.
But image action ignore parameter settings.

~~~
http://ip_addr/action?param1=value1&param2=value2&...
~~~

## Actions and parameters

| action |  |available parameters |
|--------|------|-------|
| circle | draw circle   | rotation, x, y, r, color, fill|
| clear  | clear screen  | bg |
| image  | draw image    |rotation|
| line   | draw line | rotation,x0, y0, x1, y1, color |
| text   | draw text | rotation, text, tx, ty, color, bg, text_size, obscure,clear|
| pset | draw poiint | rotation,x, y, color |
| rect | draw rectangle | rotation,x, y, w, h, color, fill |
| roundrect | draw round rectangle| rotation, x, y, w, h, r, color, fill|
| set     | set parameters only, draw nothing|   |

## Parameters

Values of almost parameters are kept between actions.
But text position parameters (tx,ty) and
clear parameter for text action are not kept.

|name|type|meaning|initial value|
|----|------|------|-------|
|bg   | color |background colr| #000000|
|clear| boolean |clear screen before action|false|
|color| color |drawing color| #ffffff| 
|fill | boolean | to be filled | false|
|h  | integer | height of rectangle | 50 |
|obscure | boolean | draw background for text action | false| 
|r  | integer | radius of cicle and round rectangle| 5 |
|rotation|integer|axies rotation 0 .. 3 |3|
|text_size| integer | text size | 2|
|text|string|string to be drawed |''|
|tx  |integer | x position of text| 0 | 
|ty  |integer | y position of text| 0 | 
|w  | integer | width of rectangle | 50 | 
|x  | integer | x position | 0 | 
|x0 | integer | x position of point 0| 319 | 
|x1 | integer | x position of point 1| 0 | 
|y  | integer | y position  | 0 | 
|y0 | integer | y position of point 0 |239|
|y1 | integer | y position of point 1 |0 | 
