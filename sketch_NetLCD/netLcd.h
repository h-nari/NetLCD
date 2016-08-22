#include "HSES_LCD24.h"

extern HSES_LCD24 tft;

typedef struct {
  int16_t tx;
  int16_t ty;
  int16_t x;
  int16_t y;
  int16_t x0;
  int16_t y0;
  int16_t x1;
  int16_t y1;
  int16_t w;
  int16_t h;
  int16_t r;
  int16_t text_size;
  int16_t rotation;
  uint16_t color;
  uint16_t bg_color;
  bool fill;
  bool obscure;
  bool clear;
  String text;
} lcd_cont_t;


typedef const struct _param_s {
  const char *name;
  void *ptr;
  bool (*handler)(const struct _param_s *ent, const char *str);
  const char *init_value;
} param_t;

extern lcd_cont_t lcd_cont;
extern param_t param_table[];

bool param_color_handler(param_t *ent, const char *str);




