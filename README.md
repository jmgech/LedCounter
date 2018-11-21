# LedCounter
This sketch fetches social media statuses from a web page.

The board will attempt to connect to a web page at boot, and return a JSON array of social network field values. The page is currently purposefully very sparse as to allow for custom implementation.

In order to run, the PHP page must reside on an accessible server, and the **DATA_PROVIDER** field needs to be defined in *config*.h.

## Icons

Icons are defined in the main *header.h* file. They are stored in flash memory in order to access them more quickly using [PROGMEM](https://www.arduino.cc/reference/en/language/variables/utilities/progmem/).

Each icon is composed of a 2 dimensional byte array of 8x8 to reproduce each NeoPixel panel and can display up to 3 colors by design .

```c++
 const byte PROGMEM _SkullIcon[8][8] = {
  {0, 2, 2, 2, 2, 2, 2, 0},
  {2, 2, 2, 2, 2, 2, 2, 2},
  {2, 1, 1, 2, 2, 1, 1, 2},
  {2, 1, 1, 2, 2, 1, 1, 2},
  {2, 2, 2, 2, 2, 2, 2, 2},
  {2, 2, 2, 2, 2, 2, 2, 2},
  {0, 2, 2, 1, 1, 2, 2, 0},
  {0, 2, 2, 1, 1, 2, 2, 0}
};

const RGB PROGMEM _SkullIconColors[3] = { 
  {0, 0, 0}, //Background
  {255, 0, 0}, // eyes
  {255, 255, 255} //bone
};
```

### Drawing the icon

In the above Skull icon definition, each "line" in the array will turn on a pixel, or keep it off. This allows us to have a 8x8 ( 64 :D ) pixels canvas to draw our icons.

Looking at the first array item, we see that the first and final pixels are left off (black) and that the other 6 pixels are set at a value of 2. This means that the pixel is turned on, and that it will use the 2 color from the RGB color array.

### Colors

In the case of the Skull icon above, each pixel is either on (1 or 2) or off (0). The on values of either 1 or 2 will define which RGB color it is to pick from the RGB Struct.

* Array[0] from the RGB struct is set at {0, 0, 0}, the pixels will be set to off
* Array[1] from the RGB struct is set at {255, 0, 0}, the pixels will be set to red
* Array[2] from the RGB struct is set at {255, 255, 255}, the pixels will be set to white

To create your own icon, you can use add your own arrays such as _MyCustomIcon\[8\]\[8\] and _MyCustomIconColors\[3\].

## Configuration Parameters

### config.h

* BRIGHTNESS - This percentage value will set the brightness of the NeoMatrix pannels. They are very bright, I usually run them at 25%.
* PIN - Set your default ESP8266 pin number

# Debug Mode

To disable the debug mode and hide serial output, you can remove **#define DEBUG** from line 1 of *SocialMediaCounter*.ino.

Jeremy