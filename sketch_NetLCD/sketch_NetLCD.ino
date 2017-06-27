#include "conf.h"

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Adafruit_GFX.h>				// https://github.com/adafruit/Adafruit-GFX-Library
#include <Fontx.h>							// https://github.com/h-nari/Fontx
#include <Humblesoft_GFX.h>			// https://github.com/h-nari/Humblesoft_GFX
#ifdef USE_ILI9341
#include <Humblesoft_ILI9341.h>	// https://github.com/h-nari/Humblesoft_ILI9341
#elif defined(USE_SSD1306)
#include <Humblesoft_SSD1306.h>
#else
#error "you must set USE_ILI9341 or USE_SSD1306"
#endif

#include "netLcd.h"

#ifdef USE_KANJI
#include <fontx/ILGH16XB.h>
#include <fontx/ILGZ16XB.h>
RomFontx fontx(ILGH16XB,ILGZ16XB);
#endif

#ifdef USE_ILI9341
#define LCD_CS	 2
#define LCD_DC	15
#define LCD_RST	-1
Humblesoft_ILI9341 dpy(LCD_CS,LCD_DC,LCD_RST);
#endif
#ifdef USE_SSD1306
#define OLED_DC		  15
#define OLED_RESET	16	
#define OLED_CS		   2

Humblesoft_SSD1306 dpy(OLED_DC, OLED_RESET, OLED_CS);
const uint16_t white = Humblesoft_SSD1306::WHITE;
const uint16_t black = Humblesoft_SSD1306::BLACK;
#endif

const char* ssid     = WIFI_SSID;
const char* password = WIFI_PASSWORD;

ESP8266WebServer server(80);
lcd_cont_t lcd_cont;

typedef const struct _uri_ent_s {
  const char *uri;
  void (*handler)(const struct _uri_ent_s *ent);
} uri_ent_t;

uri_ent_t uri_list[] = {
  {"/"},
  {"/set"},
  {"/clear", [](uri_ent_t *ent){
      dpy.fillScreen(lcd_cont.bg_color);
      dpy.setCursor(0,0);
    }},
  {"/print", [](uri_ent_t *ent){
      if(lcd_cont.clear)
				dpy.fillScreen(lcd_cont.bg_color);
      if(lcd_cont.obscure)
				dpy.setTextColor(lcd_cont.color, lcd_cont.bg_color);
      else
				dpy.setTextColor(lcd_cont.color);
      dpy.print(lcd_cont.text);
#ifdef USE_SSD1306
			if(lcd_cont.flush)
				dpy.display();
#endif
  }},
  {"/pset",[](uri_ent_t *ent){
      dpy.fillRect(lcd_cont.x, lcd_cont.y, 1, 1, lcd_cont.color);
    }},
  {"/line",[](uri_ent_t *ent){
      dpy.drawLine(lcd_cont.x0, lcd_cont.y0, lcd_cont.x1, lcd_cont.y1,
		   lcd_cont.color);
    }},
  {"/rect",[](uri_ent_t *ent){
      int16_t x,y,w,h;
      if(lcd_cont.w > 0){ x = lcd_cont.x; w = lcd_cont.w;}
      else { x = lcd_cont.x + lcd_cont.w; w = -lcd_cont.w;}
      if(lcd_cont.h > 0){ y = lcd_cont.y; h = lcd_cont.h;}
      else { y = lcd_cont.y + lcd_cont.h; h = -lcd_cont.h;}
      
      if(lcd_cont.fill)
				dpy.fillRect(x, y, w, h, lcd_cont.color);
      else
				dpy.drawRect(x, y, w, h, lcd_cont.color);
    }},
  {"/roundrect",[](uri_ent_t *ent){
      int16_t x,y,w,h;
      if(lcd_cont.w > 0){ x = lcd_cont.x; w = lcd_cont.w;}
      else { x = lcd_cont.x + lcd_cont.w; w = -lcd_cont.w;}
      if(lcd_cont.h > 0){ y = lcd_cont.y; h = lcd_cont.h;}
      else { y = lcd_cont.y + lcd_cont.h; h = -lcd_cont.h;}

      if(w >= lcd_cont.r*2 && h >= lcd_cont.r*2){ 
				if(lcd_cont.fill)
					dpy.fillRoundRect(x, y, w, h, lcd_cont.r, lcd_cont.color);
				else
					dpy.drawRoundRect(x, y, w, h, lcd_cont.r, lcd_cont.color);
      }
    }},
  {"/circle",[](uri_ent_t *ent){
      if(lcd_cont.fill)
	dpy.fillCircle(lcd_cont.x, lcd_cont.y, lcd_cont.r, lcd_cont.color);
      else
	dpy.drawCircle(lcd_cont.x, lcd_cont.y, lcd_cont.r, lcd_cont.color);
    }},
  {"/image"},
  {NULL}
};

void handleRoot() {
  server.send(200, "text/html",
	      "<h1>NetLCD server</h1>"
	      "<p>see <a href='https://github.com/h-nari/NetLCD'>"
	      "https://github.com/h-nari/NetLCD</a></p>"
	      );
}

void handleCommand() {
  String s = server.uri();
  const char *uri = s.c_str();

  lcd_cont.clear = false;
	lcd_cont.flush = false;
  
  for(int i=0; i<server.args(); i++){
    String name  = server.argName(i);
    String value = server.arg(i);
    
    param_t *p;
    for(p = param_table; p->name; p++){
      if(name== p->name){
				if(p->handler && !p->handler(p, value.c_str())){
					String mes = "Bad value:";
					mes += value;
					mes += " found for param:";
					mes += name;
					server.send(404, "text/plain", mes);
					return;
				}
				break;
      }
    }
    
    if(!p->name){
      String mes = "Undefined param:";
      mes += name;
      mes += " found. available params are ";
      for(p = param_table; p->name; p++){
				mes += p->name;
				if(p[1].name) mes += p[2].name ? "," : " and ";
      }
      server.send(404, "text/plain", mes);
      return;
    }
  }

  uri_ent_t *u;
  for(u=uri_list; u->uri; u++){
    if(strcmp(u->uri, uri)==0){
      if(u->handler)
				u->handler(u);
#ifdef USE_SSD1306
			if(lcd_cont.flush || lcd_cont.flush_always)
				dpy.display();
#endif
      break;
    }
  }
  
  if(!u->uri){
    String mes = "Internal Error\n\n";
    mes += "uri:";
    mes += uri;
    mes += " not defined.";
    server.send(404, "text/plain", mes);
    return; 
  }
  
  server.send(200, "text/plain", "Ok");
}

static bool getInt(const char *str, int *pVal, const char **pEnd)
{
  const char *p0;
  int v;

  v = strtol(str, (char **)&p0, 10);
  if(p0 != str){
    if(pVal) *pVal = v;
    if(pEnd) *pEnd = p0;
    return true;
  }
  return false;
}

#ifdef USE_SSD1306
void handleImageData_ssd1306(uint8_t *buf, uint32_t size)
{
	int x = lcd_cont.image_cx;
	int y = lcd_cont.image_cy;
	for(uint8_t *p = buf; p < buf+size; p++){
		for(uint8_t m = 0x80; m && x < lcd_cont.image_w; m >>= 1){
			dpy.drawPixel(lcd_cont.image_x + x, lcd_cont.image_y + y,
										*p & m ? white : black);
			x++;
		}
		if(x >= lcd_cont.image_w) {
			x = 0;
			if(y++ >= lcd_cont.image_h)
				break;
		}
	}
	lcd_cont.image_cx = x;
	lcd_cont.image_cy = y;
}
#endif

void handleImage()
{
  static unsigned long start_ms;
  HTTPUpload& upload = server.upload();
  if(upload.status == UPLOAD_FILE_START){
    int w = 240, h=240, x = 0, y=0;
    const char *p;

    start_ms = millis();
    
    if(getInt(upload.filename.c_str(), &w, &p) &&
       getInt(p+1, &h, &p) && getInt(p+1, &x, &p))
      getInt(p+1, &y, NULL);

#ifdef USE_ILI9341
		dpy.spi_begin();
    dpy.setAddrWindow(x, y, x+w-1, y+h-1);
		dpy.spi_end();
#elif defined(USE_SSD1306)
		lcd_cont.image_x  = x;
		lcd_cont.image_y  = y;
		lcd_cont.image_w = w;
		lcd_cont.image_h = h;
		lcd_cont.image_cx = 0;
		lcd_cont.image_cy = 0;
#endif
  }
  else if(upload.status == UPLOAD_FILE_WRITE){
#ifdef USE_ILI9341
		dpy.spi_begin();
    dpy.writedata(upload.buf, upload.currentSize);
		dpy.spi_end();
#elif defined(USE_SSD1306)
		handleImageData_ssd1306(upload.buf, upload.currentSize);
#endif
  }
  else if(upload.status == UPLOAD_FILE_END){
#ifdef USE_SSD1306
		if(lcd_cont.flush || lcd_cont.flush_always){
			Serial.println("image flush");
			dpy.display();
		}
#endif
    unsigned long now = millis();
    Serial.print("image loading time: ");
    Serial.print(now - start_ms);
    Serial.println(" ms");
  }
  else {
    Serial.print("Upload unknown status:");
    Serial.println(upload.status);
  }
}

void handleNotFound()
{
  String mes = "URI Not Defined\n\n";
  mes += "URI: ";
  mes += server.uri();
  mes += " not defined. ";
  mes += "available uri's are ";
  for(uri_ent_t *p = uri_list; p->uri; p++){
    mes += p->uri;
    if(p[1].uri) mes += p[2].uri ? "," : " and ";
  }
  mes += ".\n";
  server.send(404, "text/plain", mes);
}

void setup(void)
{
  Serial.begin(115200);
	delay(100);
	Serial.println("\n\nReset:");
#ifdef USE_ILI9341
  dpy.begin();
#elif defined(USE_SSD1306)
	dpy.begin();
	dpy.setTextColor(white);
#endif
	
#ifdef USE_KANJI 
  dpy.setFont(&fontx);
#endif
	
  for(param_t *p = param_table;p->name;p++){
    if(p->init_value && !p->handler(p, p->init_value)){
      Serial.print("Initialize error for param:");
      Serial.print(p->name);
      Serial.print(" value:");
      Serial.print(p->init_value);
      Serial.println();
    }
  }
  dpy.fillScreen(lcd_cont.bg_color);
  dpy.setCursor(lcd_cont.x, lcd_cont.y);

  Serial.println("Initialize");
  dpy.println("Initialize");
  
  WiFi.begin(ssid, password);
  Serial.print("connecting");
  dpy.print("connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    dpy.print(".");
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  dpy.println();
#ifdef USE_ILI9341
  dpy.println("connected.");
  dpy.print("IP addr: ");
  dpy.setTextColor("GREEN");
  dpy.println(WiFi.localIP());
  dpy.setTextColor("WHITE");
#elif defined(USE_SSD1306)
  dpy.println(WiFi.localIP());
#endif

  for(uri_ent_t *p=uri_list; p->uri; p++){ 
    if(strcmp(p->uri,"/")==0)
      server.on(p->uri, handleRoot);
    else if(strcmp(p->uri,"/image")==0)
      server.on(p->uri, HTTP_POST,
		[](){server.send(200,"text/plane","");},
		handleImage);
    else
      server.on(p->uri, handleCommand);
  }
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
  dpy.println("start");
}

void loop(void){
  server.handleClient();
#ifdef USE_SSD1306
	static unsigned long t;
	unsigned long now = millis();
	if(dpy.modified() && (now - t > 100)){
		t = now;
		dpy.display();
		Serial.println("display");
	}
#endif
}

/*** Local variables: ***/
/*** tab-width:2      ***/
/*** truncate-lines:t ***/
/*** End:             ***/

