#include "netLcd.h"

typedef const struct {
  const char *name;
  uint16_t value;
} color_name_t;

color_name_t color_names[] = {
#ifdef USE_ILI9341
  {"BLACK",	  0x0000},
  {"LIGHTGREY",	  0xc618},
  {"DARKGREY",	  0x7bef},
  {"BLUE",	  0x001f},
  {"GREEN",	  0x07e0},
  {"RED",	  0xf800},
  {"YELLOW",	  0xffe0},
  {"WHITE",	  0xffff},
  {"PINK",	  0xf81f},
#elif defined(USE_SSD1306)
  {"WHITE",	  Humblesoft_SSD1306::WHITE},
  {"BLACK",	  Humblesoft_SSD1306::BLACK},
#endif
  {NULL, 0},
};


static bool getHex(const char *s, int *pVal)
{
  int i,vv=0;

  for(i=0; i<2; i++){
    int v;
    if(!isxdigit(s[i]))
      return false;
    if(s[i] > 'f') return false;
    else if(s[i] >= 'a') v = s[i] - 'a' + 10;
    else if(s[i] > 'F') return false;
    else if(s[i] >= 'A') v = s[i] - 'A' + 10;
    else if(s[i] > '9') return false;
    else if(s[i] >= '0') v = s[i] - '0';
    else return false;
    vv = vv * 16 + v;
  }
  *pVal = vv;
  return true;
}

bool param_color_handler(param_t *ent, const char *str)
{
  uint16_t *pColor = (uint16_t *)ent->ptr;

  if(*str == '#'){
    int r,g,b;
    if(getHex(str+1, &r) && getHex(str+3, &g) && getHex(str+5, &b)) {
      *pColor = dpy.rgb(r,g,b);
      return true;
    }
    Serial.print("Bad color:\"");
    Serial.print(str);
    Serial.println("\" found.");
    return false;
  }
  else {
    color_name_t *p;
    for(p=color_names; p->name; p++){
      if(stricmp(str, p->name)==0){
	*pColor = p->value;
	return true;
      }
    }
    Serial.print("Undefined color name:");
    Serial.print(str);
    Serial.println(" found.");
    return false;
  }
}

