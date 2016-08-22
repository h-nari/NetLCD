from sys import argv
from PIL import Image, ImageDraw, ImageFont
import netLcd

font = '/c/Windows/Fonts/HGRGE.TTC'
size = 40
text = 'こんにちは世界'

if len(argv) < 2:
    print("Usage:%s ip_addr [font.ttc [size [text]]]" % argv[0])
    print("example: %s 192.168.0.101 /c/Windows/Fonts/HGRPP1.TTC 50 Hello" %
          argv[0]);
    exit(1)

if len(argv) > 2: font = argv[2]      
if len(argv) > 3: size = int(argv[3]) 
if len(argv) > 4: text = argv[4]      

nd = netLcd.NetLcd(argv[1])
im = Image.new('RGB', (nd.width, nd.height),'#ffffff')

draw = ImageDraw.Draw(im)
font = ImageFont.truetype( font, size)
draw.text((5,50), text, fill='#000000', font=font)
nd.disp_image(im)


