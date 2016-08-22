#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "HSES_LCD24.h"

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "conf.h"
#include "netLcd.h"


// #define CS_PIN	2
// #define DC_PIN	13
// #define RST_PIN	-1
// HSES_LCD24 tft = HSES_LCD24(CS_PIN, DC_PIN, RST_PIN);

HSES_LCD24 tft = HSES_LCD24();	// default connection CS-IO2,DC-IO13,RST-NC 

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
      tft.fillScreen(lcd_cont.bg_color);
      tft.setCursor(0,0);
    }},
  {"/print", [](uri_ent_t *ent){
      if(lcd_cont.clear)
	tft.fillScreen(lcd_cont.bg_color);
      if(lcd_cont.obscure)
	tft.setTextColor(lcd_cont.color, lcd_cont.bg_color);
      else
	tft.setTextColor(lcd_cont.color);
      tft.print(lcd_cont.text);
  }},
  {"/pset",[](uri_ent_t *ent){
      tft.fillRect(lcd_cont.x, lcd_cont.y, 1, 1, lcd_cont.color);
    }},
  {"/line",[](uri_ent_t *ent){
      tft.drawLine(lcd_cont.x0, lcd_cont.y0, lcd_cont.x1, lcd_cont.y1,
		   lcd_cont.color);
    }},
  {"/rect",[](uri_ent_t *ent){
      int16_t x,y,w,h;
      if(lcd_cont.w > 0){ x = lcd_cont.x; w = lcd_cont.w;}
      else { x = lcd_cont.x + lcd_cont.w; w = -lcd_cont.w;}
      if(lcd_cont.h > 0){ y = lcd_cont.y; h = lcd_cont.h;}
      else { y = lcd_cont.y + lcd_cont.h; h = -lcd_cont.h;}
      
      if(lcd_cont.fill)
	tft.fillRect(x, y, w, h, lcd_cont.color);
      else
	tft.drawRect(x, y, w, h, lcd_cont.color);
    }},
  {"/roundrect",[](uri_ent_t *ent){
      int16_t x,y,w,h;
      if(lcd_cont.w > 0){ x = lcd_cont.x; w = lcd_cont.w;}
      else { x = lcd_cont.x + lcd_cont.w; w = -lcd_cont.w;}
      if(lcd_cont.h > 0){ y = lcd_cont.y; h = lcd_cont.h;}
      else { y = lcd_cont.y + lcd_cont.h; h = -lcd_cont.h;}

      if(w >= lcd_cont.r*2 && h >= lcd_cont.r*2){ 
	if(lcd_cont.fill)
	  tft.fillRoundRect(x, y, w, h, lcd_cont.r, lcd_cont.color);
	else
	  tft.drawRoundRect(x, y, w, h, lcd_cont.r, lcd_cont.color);
      }
    }},
  {"/circle",[](uri_ent_t *ent){
      if(lcd_cont.fill)
	tft.fillCircle(lcd_cont.x, lcd_cont.y, lcd_cont.r, lcd_cont.color);
      else
	tft.drawCircle(lcd_cont.x, lcd_cont.y, lcd_cont.r, lcd_cont.color);
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

    tft.setAddrWindow(x, y, x+w-1, y+h-1);
  }
  else if(upload.status == UPLOAD_FILE_WRITE){
    tft.writedata(upload.buf, upload.currentSize);
  }
  else if(upload.status == UPLOAD_FILE_END){
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
  tft.begin();

  for(param_t *p = param_table;p->name;p++){
    if(p->init_value && !p->handler(p, p->init_value)){
      Serial.print("Initialize error for param:");
      Serial.print(p->name);
      Serial.print(" value:");
      Serial.print(p->init_value);
      Serial.println();
    }
  }
  tft.fillScreen(lcd_cont.bg_color);
  tft.setCursor(lcd_cont.x, lcd_cont.y);

  Serial.println("\n\nInitialize");
  tft.println("Initialize");
  
  WiFi.begin(ssid, password);
  Serial.print("connecting");
  tft.print("connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    tft.print(".");
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  tft.println();
  tft.println("connected.");
  tft.print("IP addr: ");
  tft.setTextColor(ILI9341_GREEN);
  tft.println(WiFi.localIP());
  tft.setTextColor(ILI9341_WHITE);

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
  tft.println("start");
}

void loop(void){
  server.handleClient();
}


