#include "netLcd.h"

typedef const struct {
  const char *name;
  uint16_t value;
} color_name_t;

color_name_t color_names[] = {
  {"BLACK",	  ILI9341_BLACK},
  {"LIGHTGREY",	  ILI9341_LIGHTGREY},
  {"DARKGREY",	  ILI9341_DARKGREY},
  {"BLUE",	  ILI9341_BLUE},
  {"GREEN",	  ILI9341_GREEN},
  {"RED",	  ILI9341_RED},
  {"YELLOW",	  ILI9341_YELLOW},
  {"WHITE",	  ILI9341_WHITE},
  {"PINK",	  ILI9341_PINK},
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
      *pColor = tft.color565(r,g,b);
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

