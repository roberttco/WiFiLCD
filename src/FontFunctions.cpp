#include <Arduino.h>
#include "WiFiLCD.hpp"
#include "FontFunctions.hpp"

static FontMap fmap[NUMFONTS] = {
  {"FreeMono",      (GFXfont *)(&FreeMono9pt7b)},
  {"FreeSans",      (GFXfont *)(&FreeSans9pt7b)},
  {"Varela_r_10",   (GFXfont *)(&varela_regular10pt7b)},
  {"Varela_r_15",   (GFXfont *)(&varela_regular15pt7b)},
  {"Varela_r_20",   (GFXfont *)(&varela_regular20pt7b)},
  {"Futuri_r_60",   (GFXfont *)(&Futuri_Condensed_Regular60pt7b)},
  {"Futuri_r_50",   (GFXfont *)(&Futuri_Condensed_Regular50pt7b)},
  {"Futuri_r_40",   (GFXfont *)(&Futuri_Condensed_Regular40pt7b)},
  {"Futuri_lo_40",  (GFXfont *)(&Futuri_Condensed_Light_Oblique40pt7b)},
  {"Futuri_lo_50",  (GFXfont *)(&Futuri_Condensed_Light_Oblique50pt7b)},
  {"Futuri_lo_60",  (GFXfont *)(&Futuri_Condensed_Light_Oblique60pt7b)}
};

bool CompareFontNames(char *name, char *compare)
{
  int namelen = strlen(name);
  int comparelen = strlen(compare);
  if (namelen < comparelen)
  {
    return false;
  }
  
  for (int i = 0; i < namelen; i++)
  {
    if (compare[i] != name[i]) return false;
  }

  return true;
}

GFXfont *GetFont(char *name)
{
  DEBUG_PRINT ("Looking for font named ");
  DEBUG_PRINTLN(name);
  
  int numfonts = sizeof(fmap) / sizeof(FontMap);

  for (int i = 0 ; i < numfonts ; i++)
  {
    DEBUG_PRINTLN (fmap[i].name);
    
    if (CompareFontNames(fmap[i].name,name) == true)
    {
      return fmap[i].font;  
    }
  }

  DEBUG_PRINTLN("Not found");
  return NULL;
}
