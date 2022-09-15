#include <Arduino.h>

#include "WiFiLCD.hpp"

#include <CmdCallback.hpp>
#include <CmdParser.hpp>

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <EspMQTTClient.h>

#include "GFXPrimitiveHandlers.hpp"

// Check out https://chrishewett.com/blog/true-rgb565-colour-picker/ to pick colors


// initialize ST7789 TFT library with hardware SPI module
// SCK (CLK) ---> NodeMCU pin D5 (GPIO14)
// MOSI(DIN) ---> NodeMCU pin D7 (GPIO13)
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// command parser stuff

CmdCallback<8> cmdCallbackP;
//CmdBuffer<512> myBuffer;
CmdParser     myParser;

bool connecting = true;
bool waiting = false;

// MQTT
EspMQTTClient client(
  "qsvMIMt8Fm6NV3",
  "UbKNUJakLBLpOh",
  "192.168.2.6",  // MQTT Broker server ip
  "7789Cube",     // Client name that uniquely identify your device
  24552              // The MQTT port, default to 1883. this line can be omitted
);

void setup(void)
{
  Serial.begin(115200);

  // if the display has CS pin try with SPI_MODE0
  tft.init(240, 240, SPI_MODE2);    // Init ST7789 display 240x240 pixel

  //
  tft.setRotation(3); // USB connector on the right 
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextWrap(false);

  ////
  // Enable cmd strings with "" -> SET VAL "HALLO WORLD"
  myParser.setOptIgnoreQuote(false); // default

  ////
  // Set command seperator.
  myParser.setOptSeperator(','); // default

  cmdCallbackP.addCmd("F", &functFill);
  cmdCallbackP.addCmd("S", &functString);
  cmdCallbackP.addCmd("SX", &functStringExtended);
  cmdCallbackP.addCmd("R", &functRectangle);
  cmdCallbackP.addCmd("C", &functCircle);
  cmdCallbackP.addCmd("T", &functTriangle);
  cmdCallbackP.addCmd("P", &functPixel);
  cmdCallbackP.addCmd("L", &functCircle);

  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
  client.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overrited with enableHTTPWebUpdater("user", "password").
  client.enableLastWillMessage("7133egyptian/out/display1/state", "Offline");  // You can activate the retain flag by setting the third parameter to true
}

int connectingRadius = 1;
void loop(void)
{
  client.loop();

  if (connecting || waiting)
  {
      tft.drawCircle(120,120, connectingRadius, ST77XX_BLACK);
      connectingRadius += 8;
      if (connectingRadius > 110)
      {
        connectingRadius = 0;
      }
      
      tft.drawCircle(120,120, connectingRadius, (waiting ? random(ST77XX_BLACK,ST77XX_WHITE) : ST77XX_WHITE));

      delay(100);
  }
//  else
//  {
//    cmdCallback.updateCmdProcessing(&myParser, &myBuffer, &Serial);
//  }
}

void onConnectionEstablished()
{
  // Subscribe to "7133egyptian/in/display1" and display received message to Serial
  client.subscribe("7133egyptian/in/display1/lcd", [](const String & payload) {
    // if waiting for an initial message and received one then clear the screen
    if (waiting)
    {
      tft.fillScreen(ST77XX_BLACK);
      waiting = false;
    }
    
    DEBUG_PRINTLN(payload);

    char *p = (char *)payload.c_str();
    char *i;
    char *token = strtok_r(p,"|",&i);
    while (token != NULL)
    {
      if (myParser.parseCmd(token) != CMDPARSER_ERROR)
      {
        cmdCallbackP.processCmd(&myParser);
      }

      token = strtok_r(NULL,"|",&i);
    }
  });

  client.subscribe("7133egyptian/in/display1/command", [](const String & payload) {
    if (waiting)
    {
      tft.fillScreen(ST77XX_BLACK);
      waiting = false;
    }
    Serial.println(payload);

    int cmd = payload.toInt();

    switch (cmd)
    {
      case 255: // clear display and home cursor
        tft.fillScreen(ST77XX_BLACK);
        tft.setCursor(0,0);
        break;
      case 0: // toggle rotation
      case 1: // toggle rotation
      case 2: // toggle rotation
      case 3: // toggle rotation
        tft.setRotation(cmd);
        break;
      default:
        break; 
    }
  });
  
  // Publish a message to "mytopic/test"
  client.publish("7133egyptian/out/display1/state", "Online"); // You can activate the retain flag by setting the third parameter to true
  
  connecting = false;
  waiting = true;
  //tft.fillScreen(ST77XX_BLACK);
}
