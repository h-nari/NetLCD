from sys import argv
import time
from PIL import Image
import netLcd

usage = '%s ip_addr image_file'

wait_time = 2;
if len(argv) < 3:
    print(usage % argv[0])
    exit(1)

nd = netLcd.NetLcd(argv[1])
size = (128, 64)

file = argv[2]
im = Image.open(file)
im.thumbnail(size)
im2 = Image.new('RGB',size)
ox = int((im2.width  - im.width)/2)
oy = int((im2.height - im.height)/2)
im2.paste(im, (ox,oy))
nd.disp_image_ssd1306(im2)

