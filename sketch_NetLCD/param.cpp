#include "netLcd.h"

static bool
param_string_handler( param_t *ent, const char *str)
{
  String *s = (String *)ent->ptr;
  *s = str ? str : "";
  return true;
}

static bool param_int_handler(param_t *ent, const char *str)
{
  char *end;
  int v = strtol(str, &end, 0);
  if(*end) return false;
  *(int16_t *)ent->ptr = v;
  return true;
}

static bool
param_textsize_handler(param_t *ent, const char *str)
{
  bool r = param_int_handler(ent, str);

  if(r) 
    tft.setTextSize(lcd_cont.text_size);
  return r;
}

static bool
param_rotation_handler(param_t *ent, const char *str)
{
  bool r = param_int_handler(ent, str);
  if(r)
    tft.setRotation(lcd_cont.rotation);
  return r;
}

static bool param_tx_handler(param_t *ent,const char *str)
{
  bool r = param_int_handler(ent, str);
  
  if(r) tft.setCursor( lcd_cont.tx, tft.getCursorY());
  return r;
}

static bool param_ty_handler(param_t *ent,const char *str)
{
  bool r = param_int_handler(ent, str);
  if(r) tft.setCursor( tft.getCursorX(), lcd_cont.ty);
  return r;
}

static bool param_bool_handler(param_t *ent, const char *str)
{
  char c = str[0];
  
  if(c == 't' || c == 'T' || c == '1')
    *(bool *)ent->ptr = true;
  else if(c == 'f' || c == 'F' || c == '0')
    *(bool *)ent->ptr = false;
  else
    return false;
  return true;
}

param_t param_table[] = {
  {"bg", &lcd_cont.bg_color, param_color_handler, "black"},
  {"clear", &lcd_cont.clear, param_bool_handler, "false"},
  {"color", &lcd_cont.color, param_color_handler, "white"},
  {"fill", &lcd_cont.fill, param_bool_handler, "false"},
  {"h", &lcd_cont.h, param_int_handler, "50"},
  {"obscure", &lcd_cont.obscure, param_bool_handler, "false"},
  {"r", &lcd_cont.r, param_int_handler, "5"},
  {"rotation",  &lcd_cont.rotation, param_rotation_handler, "3"},
  {"text", &lcd_cont.text, param_string_handler, NULL},
  {"text_size", &lcd_cont.text_size, param_textsize_handler, "2"},
  {"tx", &lcd_cont.tx, param_tx_handler, NULL},
  {"ty", &lcd_cont.ty, param_ty_handler, NULL},
  {"w", &lcd_cont.w, param_int_handler, "50"},
  {"x", &lcd_cont.x, param_int_handler,  "0"},
  {"x0", &lcd_cont.x0, param_int_handler, "0"},
  {"x1", &lcd_cont.x1, param_int_handler, "319"},
  {"y", &lcd_cont.y, param_int_handler,  "0"},
  {"y0", &lcd_cont.y0, param_int_handler, "0"},
  {"y1", &lcd_cont.y1, param_int_handler, "239"},
  {NULL},
};
