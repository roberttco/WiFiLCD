#ifndef __FONT_FUNCTIONS_H_
#define __FONT_FUNCTIONS_H_

#include <Adafruit_GFX.h>    // Core graphics library

#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeSans9pt7b.h>

#include <Fonts/varela_regular10pt7b.h>
#include <Fonts/varela_regular15pt7b.h>
#include <Fonts/varela_regular20pt7b.h>

#include <Fonts/Futuri_Condensed_Regular40pt7b.h>
#include <Fonts/Futuri_Condensed_Regular50pt7b.h>
#include <Fonts/Futuri_Condensed_Regular60pt7b.h>

#include <Fonts/Futuri_Condensed_Light_Oblique40pt7b.h>
#include <Fonts/Futuri_Condensed_Light_Oblique50pt7b.h>
#include <Fonts/Futuri_Condensed_Light_Oblique60pt7b.h>

typedef struct _FontMap
{
  char *name;
  GFXfont *font;
} FontMap;

bool CompareFontNames(char *name, char *compare);
GFXfont *GetFont(char *name);

#endif