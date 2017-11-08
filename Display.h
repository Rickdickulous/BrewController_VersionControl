#ifndef Display_h
#define Display_h

#include "Arduino.h"
#include "Adafruit_ILI9341.h"
#include "Utils.h"

// For the Adafruit shield, these are the default.
    #define TFT_DC 9
    #define TFT_CS 10

class Display
{
public:

    Display(){};

    Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
	  void init(Utils&);
	  void drawSquare();
    void printOnScreen(Utils&);
    void test();

	~Display(){};
};

#endif // Display_h
