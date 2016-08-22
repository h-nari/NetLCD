#include "HSES_LCD24.h"
#include <SPI.h>

HSES_LCD24::HSES_LCD24(int8_t cs, int8_t dc, int8_t rst) :
  Adafruit_ILI9341(cs, dc, rst) {
  __cs = cs;
  __dc = dc;
}

void HSES_LCD24::writedata(uint8_t *data, uint32_t len)
{
  digitalWrite(__dc, HIGH);
  digitalWrite(__cs, LOW);
  SPI.writeBytes(data, len);
  digitalWrite(__cs, HIGH);
}
