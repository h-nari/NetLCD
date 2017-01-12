# VERBOSE := 1
SINGLE_THREAD := 1
USE_PREBUILD := 1

ESP_ADDR := "192.168.0.203"
ESP_PORT := 8266
ESP_PWD  := "f7ojx7f0"

EA_DIR := C:/Users/nari/AppData/Local/Arduino15/packages/esp8266/
HLIB_DIR := $(EA_DIR)/hardware/esp8266/2.3.0/libraries
ULIB_DIR := C:/Users/nari/documents/Arduino/libraries

LIBS :=
LIBS += $(HLIB_DIR)/SPI
LIBS += $(HLIB_DIR)/Wire
LIBS += $(HLIB_DIR)/ESP8266WiFi
LIBS += $(HLIB_DIR)/ESP8266WebServer
LIBS += $(HLIB_DIR)/ESP8266mDNS
LIBS += $(HLIB_DIR)/ArduinoOTA

# LIBS += $(HLIB_DIR)/ESP8266HTTPClient
LIBS += $(ULIB_DIR)/Adafruit-GFX-Library
LIBS += $(ULIB_DIR)/Adafruit_ILI9341
LIBS += $(ULIB_DIR)/Fontx/src
LIBS += $(ULIB_DIR)/Humblesoft_ILI9341/src
LIBS += $(ULIB_DIR)/Humblesoft_GFX/src
LIBS += $(ULIB_DIR)/Humblesoft_SSD1306/src

include makeEspArduino.mk

