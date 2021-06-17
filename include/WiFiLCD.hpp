#ifndef __WIFILCD_H_
#define __WIFILCD_H_

#include <Adafruit_ST7789.h>
#include <CmdCallback.hpp>
#include <CmdParser.hpp>

#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINT(X) Serial.print(X)
#define DEBUG_PRINTLN(X) Serial.println(X)
#define DEBUG_DUMPPARAMS(X) dumpParams(X)
#else
#define DEBUG_PRINT(X)
#define DEBUG_PRINTLN(X)
#define DEBUG_DUMPPARAMS(X)
#endif

#define NUMFONTS 11


// ST7789 TFT module connections
#define TFT_DC    D1     // TFT DC  pin is connected to NodeMCU pin D1 (GPIO5)
#define TFT_RST   D2     // TFT RST pin is connected to NodeMCU pin D2 (GPIO4)
#define TFT_CS    -1     // TFT CS  pin is connected to NodeMCU pin D8 (GPIO15)

extern Adafruit_ST7789  tft;

#endif