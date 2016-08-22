import time
import netLcd
from sys import argv
from PIL import Image
from datetime import datetime

usage = '%s ip_addr'
if len(argv) < 2:
    print(usage % argv[0])
    exit(1)
    
nd = netLcd.NetLcd(argv[1])

nd.clear(obscure=1)
day0 = sec0 = -1

while(1):
    now = datetime.now();
    if day0 != now.day:
        s = now.strftime("%Y/%m/%d(%a)")
        nd.text(s, color='#8080ff',tx=20,ty=80,text_size=3)
        day0 = now.day

    if sec0 != now.second:    
        s = now.strftime("%H:%M:%S")
        nd.text(s, color='green', tx=10, ty=120, text_size=6)
        sec0 = now.second

    time.sleep(0.1)
    
