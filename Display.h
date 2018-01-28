#ifndef Display_h
#define Display_h

#include "Utils.h"
#include "Arduino.h"            // Core Display Libraries
#include "Adafruit_ILI9341.h"   // Core Display Libraries
#include "Adafruit_FT6206.h"    // Touch Display Libraries


// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

// Touch screen adjusted min and max, x and y values, from https://learn.adafruit.com/adafruit-2-8-tft-touch-shield-v2/touchscreen-paint-demo
#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 3800
#define TS_MAXY 4000

// Color definitions
#define BLACK       0x0000      /*   0,   0,   0 */
#define NAVY        0x000F      /*   0,   0, 128 */
#define DARKGREEN   0x03E0      /*   0, 128,   0 */
#define DARKCYAN    0x03EF      /*   0, 128, 128 */
#define MAROON      0x7800      /* 128,   0,   0 */
#define PURPLE      0x780F      /* 128,   0, 128 */
#define OLIVE       0x7BE0      /* 128, 128,   0 */
#define LIGHTGREY   0xC618      /* 192, 192, 192 */
#define DARKGREY    0x7BEF      /* 128, 128, 128 */
#define BLUE        0x001F      /*   0,   0, 255 */
#define GREEN       0x07E0      /*   0, 255,   0 */
#define CYAN        0x07FF      /*   0, 255, 255 */
#define RED         0xF800      /* 255,   0,   0 */
#define MAGENTA     0xF81F      /* 255,   0, 255 */
#define YELLOW      0xFFE0      /* 255, 255,   0 */
#define WHITE       0xFFFF      /* 255, 255, 255 */
#define ORANGE      0xFD20      /* 255, 165,   0 */
#define GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define PINK        0xF81F

class Display
{
public:

    Display(){};

    Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
    Adafruit_FT6206 ctp = Adafruit_FT6206();
    void init();
	  void initState(Utils&);
    void printOnScreen(Utils&);
    void touchControl(Utils&);

	~Display(){};
};

extern Display disp;  // ! Important trick here - this statement makes a global object disp that when
                      //   instantiated is accessible throughout the program

#endif // Display_h
