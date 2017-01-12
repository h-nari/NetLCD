import sys
import time
import random
from PIL import Image, ImageDraw, ImageFont
import netLcd

wait_time = 2

number_of_line  = 100
number_of_rectangle = 50
number_of_circle    = 50
number_of_rrec      = 50

width = 128
height = 64

if len(sys.argv) != 2:
    print("Usage:%s ip_address" % sys.argv[0])
    exit(1)

nd = netLcd.NetLcd(sys.argv[1]);
nd.set(rotation=2,color='white',bg='black',flush_always=1)
random.seed()

# text

nd.clear(bg='black')
for i in range(100,-1,-1):
    nd.text('%03d' % i, text_size=4, tx=0, ty=0, obscure=1)
time.sleep(wait_time)    

nd.clear(bg='black')
x = 0
y = 0
for size in range(1,4):
    nd.text('size=%d\n' % size, tx = x, ty = y, text_size = size, obscure=0)
    y += size * 10
    
time.sleep(wait_time)
    
nd.clear(obscure=0,bg='black')
    
for r in range(4):
    nd.set(rotation=r)
    nd.text('rotation=%d' % r, tx=0, ty=0, text_size=1)

nd.set(rotation=2)
time.sleep(wait_time)

# line

nd.clear(bg='black')
for t in range(number_of_line):
    x0 = random.randrange(width)
    y0 = random.randrange(height)
    x1 = random.randrange(width)
    y1 = random.randrange(height)
    nd.line(x0,y0,x1,y1,color='white')

time.sleep(wait_time)

# rectangle    

nd.clear()
for t in range(number_of_rectangle):
    x0 = random.randrange(width)
    y0 = random.randrange(height)
    x1 = random.randrange(width)
    y1 = random.randrange(height)
    nd.rect(x0,y0,x1-x0,y1-y0,fill=0)
time.sleep(wait_time)

# circle

nd.clear()
for t in range(number_of_circle):
    x = random.randrange(width)
    y = random.randrange(height)
    r_max = min(x, width-x, y, height-y)
    if r_max > 1:
        r = random.randrange(1,r_max)
    else:
        r = 1
    nd.circle(x,y,r,color='white')
time.sleep(wait_time)
    
# rounded rectangle

nd.clear()
t = 0
while t < number_of_rrec:
    x0 = random.randrange(width)
    y0 = random.randrange(height)
    x1 = random.randrange(width)
    y1 = random.randrange(height)
    if(abs(x0-x1) < 5 or abs(y0-y1) < 5):
        continue
    t+=1
    r_max = int(min(abs(x0-x1),abs(y0-y1))/2)
    if r_max > 0:  
        r = random.randrange(0,r_max)
    else:
        r = 0
    c = 'white'
    nd.roundrect(x0,y0,x1-x0,y1-y0,r)
time.sleep(wait_time)

# image

nd.clear(flush_always=0)
im = Image.open('img_miku_web.jpg')
(w,h) = im.size

for m in range(3):
    im2 = im.crop((0,0,w,int(h/(1 << m))))
    im2.thumbnail((width,height))
    nd.clear()
    nd.disp_image_ssd1306(im2)
    nd.set(flush=1)
    time.sleep(wait_time)

# nd.disp_image_ssd1306(im, (width - w)/2)

sys.exit()
time.sleep(wait_time)
h = 32
nd.rect(0,height-h,width,h,color='black',fill=1)
nd.set(color='white',text_size=1);
nd.text('Hatsune Miku / CC BY-NC',tx=60,ty=height-h+2)
nd.text('Crypton FutureMedia inc.',tx=60,ty=height-h+16)
