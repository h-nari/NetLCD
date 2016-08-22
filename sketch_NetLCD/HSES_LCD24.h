#ifndef _hses_lcd24_h_
#define _hses_lcd24_h_

#include "Arduino.h"
#include "Adafruit_ILI9341.h"

class HSES_LCD24 : public Adafruit_ILI9341 {
 public:
  HSES_LCD24(int8_t _CS=2, int8_t _DC=15, int8_t _RST = -1);
  void writedata(uint8_t *data, uint32_t len);
  
 private:
  int32_t __cs,__dc;
};


#endif /* _hses_lcd24_h_ */
