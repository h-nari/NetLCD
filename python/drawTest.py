import sys
import time
import random
from PIL import Image, ImageDraw, ImageFont
import netLcd

wait_time = 2
colors = ['#0000ff','#00ff00','#00ffff','#ff0000','#ff00ff','#ffff00','#ffffff']

number_of_line  = 300
number_of_rectangle = 100
number_of_circle    = 100

if len(sys.argv) != 2:
    print("Usage:%s ip_address" % sys.argv[0])
    exit(1)

nd = netLcd.NetLcd(sys.argv[1]);
random.seed()

# text

nd.clear(bg='black')
for i in range(100,-1,-1):
    nd.text('%03d' % i, text_size=8, tx=100, ty=88, obscure=1,
            color= 'red' if i == 0 else 'white',
            bg= 'black')
time.sleep(wait_time)    

for obscure in range(2):
    nd.clear(bg='black')
    x = 5
    y = 16
    for size in range(1,7):
        nd.text('size=%d\n' % size, tx = x, ty = y, text_size = size,
                color=colors[size],bg='#808080',obscure=obscure)
        y += size * 10
    time.sleep(wait_time)
    
nd.clear(obscure=0,bg='black')
    
for r in range(4):
    nd.set(rotation=r)
    nd.text('rotation=%d' % r, tx=5, ty=20, text_size=3, color=colors[r])


time.sleep(wait_time)

# points

colors2 = ['red','green','blue']

nd.clear(rotation=3, bg='white')
noc =len(colors2)
yy = [];
for i in range(noc):
    yy.append(int(nd.height/2))

r = 3    
for x in range(nd.width):
    for i in range(noc):
        yy[i] += random.randint(-r,r)
        yy[i] = min(yy[i], nd.height-1)
        yy[i] = max(yy[i], 0)
        nd.pset(x, yy[i], color=colors2[i])

time.sleep(wait_time)

# line

nd.clear(bg='black')
for t in range(number_of_line):
    x0 = random.randrange(nd.width)
    y0 = random.randrange(nd.height)
    x1 = random.randrange(nd.width)
    y1 = random.randrange(nd.height)
    c = colors[random.randrange(7)]
    nd.line(x0,y0,x1,y1,color=c)

time.sleep(wait_time)

# rectangle    

for fill in range(2):
    nd.clear()
    for t in range(number_of_rectangle):
        x0 = random.randrange(nd.width)
        y0 = random.randrange(nd.height)
        x1 = random.randrange(nd.width)
        y1 = random.randrange(nd.height)
        c = colors[random.randrange(7)]
        nd.rect(x0,y0,x1-x0,y1-y0,color=c,fill=fill)
    time.sleep(wait_time)

# circle

for fill in range(2):
    nd.clear()
    for t in range(number_of_circle):
        x = random.randrange(nd.width)
        y = random.randrange(nd.height)
        r_max = min(x, nd.width-x, y, nd.height-y)
        if r_max > 1:
            r = random.randrange(1,r_max)
        else:
            r = 1
        c = colors[random.randrange(7)]
        nd.circle(x,y,r,color=c,fill=fill)
    time.sleep(wait_time)
    
# rounded rectangle

for fill in range(2):
    nd.clear()
    for t in range(50):
        x0 = random.randrange(nd.width)
        y0 = random.randrange(nd.height)
        x1 = random.randrange(nd.width)
        y1 = random.randrange(nd.height)
        r_max = int(min(abs(x0-x1),abs(y0-y1))/2)
        if r_max > 0:  
            r = random.randrange(0,r_max)
        else:
            r = 0
        c = colors[random.randrange(7)]
        nd.roundrect(x0,y0,x1-x0,y1-y0,r,color=c,fill=fill)
    time.sleep(wait_time)

    
# image

nd.clear()
im = Image.open('img_miku_web.jpg')
(w,h) = im.size

for m in range(2):
    im2 = im.crop((0,0,w,h/(1 << m)))
    im2.thumbnail((nd.width,nd.height))
    nd.disp_image(im2)
    time.sleep(wait_time)

nd.disp_image(im, (nd.width - w)/2)

time.sleep(wait_time)
t = 'Hatsune Miku / Crypton Future Media inc. / CC BY-NC'
nd.rect(0,nd.height-16,nd.width,16,color='black',fill=1)
nd.text(tx=0,ty=nd.height-14, color='yellow',text_size=1, text=t)
