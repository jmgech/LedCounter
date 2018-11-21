#define DEBUG

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#include <ArduinoJson.h>

#include <ESP8266HTTPClient.h>

/*
   Wifi Manager required Libraries
*/
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

#include <WiFiClientSecure.h>

/*
   Custom Libraries and Classes
*/
#include "debug.h"  // Debug M
#include "config.h"
#include "header.h"
#include "Network.h"
#include "HttpParser.h"

Network network;
HttpParser parser;
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(MATRIX_WIDTH, MATRIX_HEIGHT, NUM_TILES_X, NUM_TILES_Y, PIN,
                            NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE + NEO_TILE_TOP + NEO_TILE_LEFT + NEO_TILE_ROWS + NEO_TILE_PROGRESSIVE,
                            COLOR_ORDER + NEO_KHZ800);

void setText(String text, int cursorPosition, RGB textColor);
void setTextWithIcon(String text, int textPosition, RGB textColor, const byte (icon)[8][8],  const RGB (iconColors)[3], int iconPosition);


void setup() {

#ifdef DEBUG
  Serial.begin(115200);
  LOG("DEBUG Enabled");
  LOGF("Data Provider: %s\n", DATA_PROVIDER);
#endif

  matrix.begin();
  matrix.setBrightness(BRIGHTNESS);
  matrix.fillScreen(0);
  matrix.show(); // Clear screen from possible previous glyphs.

  setText("Setup", 1, {255, 255, 255});
  matrix.show();



  network.wifiManager(); // if required... function should check for valid connection

  resetDisplay();

  printIcon(0, _WifiIcon, _WifiIconColors);
  setText("Wifi", 9, {255, 255, 255});
  matrix.show();

  delay(1200);

  resetDisplay();

}

void loop() {


  String json = parser.readJSONFromPage(); // String * ?
  LOGF("JSON: %s\n", json.c_str());



  const size_t bufferSize = JSON_OBJECT_SIZE(4) + 60;
  DynamicJsonBuffer jsonBuffer(bufferSize);

  JsonObject& root = jsonBuffer.parseObject(json);

 
  // Should it be refreshed?
  // Check if last refresh millis is greater than 10 minutes

  unsigned long currentMillis = millis();

  if ((unsigned long)(currentMillis - lastRefresh) >= refreshInterval) {

  LOGLN("Refreshing...");
  resetDisplay();

  std::string sn[] = {"cocktail", "instagram", "youtube", "twitter"};




  setTextWithIcon(String((int)root["cocktail"]), 9, {255, 255, 255}, _CocktailIcon, _CocktailIconColors, 0);
  delay(10000);

  resetDisplay();
  setTextWithIcon(String((int)root["instagram"]), 9, {255, 255, 255}, _InstagramIcon, _InstagramIconColors, 0);
  delay(10000);

  resetDisplay();
  setTextWithIcon(String((int)root["youtube"]), 9, {255, 255, 255}, _YoutubeIcon, _YoutubeIconColors, 0);
  delay(10000);

  resetDisplay();
  setTextWithIcon(String((int)root["twitter"]), 9, {255, 255, 255}, _TwitterIcon, _TwitterIconColors, 0);
  delay(10000);


  lastRefresh = currentMillis;

  }

}


/*================== GFX Methods ==================*/

void printIcon(int startPosition, const byte (icon)[8][8], const RGB (colors)[3]) {  // was &icon and &colors

  matrix.fillScreen(0);

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {

      byte currentPixel = pgm_read_byte(&icon[i][j]);
      RGB currentColor;
      memcpy_P(&currentColor, colors + currentPixel, sizeof(RGB));

      byte red = currentColor.r;
      byte green = currentColor.g;
      byte blue = currentColor.b;

      matrix.setPixelColor(startPosition++, red, green, blue);
    }
  }

  matrix.show();

}

/*================== Text Methods ==================*/

void setTextWithIcon(String text, int textPosition, RGB textColor, const byte (icon)[8][8],  const RGB (iconColors)[3], int iconPosition = 0) {

  printIcon(iconPosition, icon, iconColors);
  setText(text, textPosition, {textColor.r, textColor.g, textColor.b});
  LOGF("Value: %s\n", text.c_str());

  matrix.show();

}

void setText(String text, int cursorPosition = 0, RGB textColor = {255, 255, 255}) {

  int baseline = 1; //0 if old font , 8 if new

  matrix.setCursor(cursorPosition, baseline);
  matrix.setTextWrap(false);
  matrix.setTextColor(matrix.Color(textColor.r, textColor.g, textColor.b));
  matrix.print(text);


}

void resetDisplay() {
  matrix.fillScreen(0);
  matrix.show(); // All pixels to off
}
