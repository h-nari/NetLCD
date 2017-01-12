import requests
import struct
import sys

class NetLcd:
    def __init__(self, ip_addr):
        self.ip_addr = ip_addr
        self.set_rotation(3)

    def set_rotation(self,r):
        if r==0 or r==2:
            self.width  = 240
            self.height = 320
        elif r==1 or r==3:
            self.width  = 320
            self.height = 240
        else:
            raise Exception('Bad rotation value:%d' % r)

    def send_request(self, cmd, dict = []):
        url = 'http://%s/%s' % (self.ip_addr, cmd)

        for retry in range(5):
            try:
                r = requests.get(url, dict)
                if r.status_code == requests.codes.ok:
                    break
            except:
                print("Unexpected error:" , sys.exc_info()[0])
                
        if retry > 5:    
            raise Exception("retry over")
        
        if 'rotation' in dict:
            self.set_rotation(dict['rotation'])
        
    def clear(self, **dict):
        self.send_request('clear',dict)

    def set(self, **dict):
        self.send_request('set',dict)

    def text(self, text, **dict):
        dict['text'] = text
        self.send_request('print',dict)

    def pset(self, x, y, **dict):
        dict['x'] = x
        dict['y'] = y
        self.send_request('pset',dict)

    def line(self,x0,y0,x1,y1, **dict):
        dict['x0'] = x0
        dict['y0'] = y0
        dict['x1'] = x1
        dict['y1'] = y1
        self.send_request('line',dict)

    def rect(self, x, y, w, h, **dict):
        dict['x'] = x
        dict['y'] = y
        dict['w'] = w
        dict['h'] = h
        self.send_request('rect',dict)

    def roundrect(self, x, y, w, h, r, **dict):
        dict['x'] = x
        dict['y'] = y
        dict['w'] = w
        dict['h'] = h
        dict['r'] = r
        self.send_request('roundrect',dict)

    def circle(self, x, y, r, **dict):
        dict['x'] = x
        dict['y'] = y
        dict['r'] = r
        self.send_request('circle',dict)
        
    def disp_image(self, im, x=0, y=0):
        x = int(x)
        y = int(y)
        (w,h) = im.size
        (x0,y0) = (max(x, 0), max(y, 0))
        (x1,y1) = (min(x+w, self.width), min(y+h,self.height))
        (ww,hh) = (x1 - x0, y1 - y0)
        (xs,ys) = (max(0, -x), max(0, -y))
        
        if w != ww or h != ww:
            im2 = im.crop((xs, ys, xs+ww, ys+hh))
        else:
            im2 = im.copy()

        img_data = b''
        for d in list(im2.getdata()):
            r,g,b = d
            rgb = ((r & 0xf8) << 8)|((g & 0xfc) << 3)|((b & 0xf8) >> 3)
            img_data += struct.pack('>H', rgb)
        files = {'file': ('%dx%d+%d+%d' % (ww,hh,x0,y0), img_data)}
        url_image = 'http://%s/image' % self.ip_addr
        r = requests.post(url_image, files=files)
        
    def disp_image_ssd1306(self, im, x=0, y=0):
        x = int(x)
        y = int(y)
        (w,h) = im.size
        (x0,y0) = (max(x, 0), max(y, 0))
        (x1,y1) = (min(x+w, self.width), min(y+h,self.height))
        (ww,hh) = (x1 - x0, y1 - y0)
        (xs,ys) = (max(0, -x), max(0, -y))
        
        if w != ww or h != ww:
            im2 = im.crop((xs, ys, xs+ww, ys+hh))
        else:
            im2 = im.copy()
            
        im3 = im2.convert(mode='1')

        print("w:%d h:%d x:%d y:%d" % (ww, hh, x0, y0))

        img_data = im3.tobytes()
        files = {'file': ('%dx%d+%d+%d' % (ww,hh,x0,y0), img_data)}
        url_image = 'http://%s/image' % self.ip_addr
        r = requests.post(url_image, files=files)

        
        

    
    
