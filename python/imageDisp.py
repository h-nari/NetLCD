from sys import argv
import time
from PIL import Image
import netLcd

usage = '%s ip_addr image_files...'

wait_time = 2;
if len(argv) < 3:
    print(usage % argv[0])
    exit(1)

nd = netLcd.NetLcd(argv[1])
size = (nd.width, nd.height)

for i in range(2,len(argv)):
    file = argv[i]
    im = Image.open(file)
    im.thumbnail(size)
    im2 = Image.new('RGB',size)
    ox = (im2.width  - im.width)/2
    oy = (im2.height - im.height)/2
    im2.paste(im, (ox,oy))
    nd.disp_image(im2)
    time.sleep(wait_time)
