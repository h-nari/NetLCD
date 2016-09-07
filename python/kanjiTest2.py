from sys import argv
from PIL import Image, ImageDraw, ImageFont
import netLcd

text = '漢字も書けます。'

if len(argv) < 2:
    print("Usage:%s ip_addr [string]" % argv[0])
    exit(1)

if len(argv) > 2: text = argv[2]      

nd = netLcd.NetLcd(argv[1])
nd.clear()
nd.text(text)


