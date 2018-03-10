#ifndef Display_h
#define Display_h

#include "Utils.h"
#include "Arduino.h"            // Core Display Libraries
#include "Adafruit_ILI9341.h"   // Core Display Libraries
#include "Adafruit_FT6206.h"    // Touch Display Libraries

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10


#define SCREEN_WIDTH_PIXELS 240
#define SCREEN_HEIGHT_PIXELS 320


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


int const Bg = DARKGREY;     // Background color
int const Tc = GREENYELLOW;  // text color


struct BoxCoords {
    int x_origin;
    int y_origin;
    int width;
    int height;
};


class Button {
public:
    Button(Utils * u_ptr) : utils_Ptr(u_ptr) {};
    virtual void checkIfAreaTouched(TS_Point&) = 0;  // executes sideEffect function
    virtual void drawButton() = 0;
    Utils * utils_Ptr;
};

class PreMash_TempUp : Button {
public:
      PreMash_TempUp(Utils * u_ptr) : Button(u_ptr) {};
      void drawButton();
      void checkIfAreaTouched(TS_Point&);
      
private:               // x,  y,  w,  h
    BoxCoords coords = {140, 50, 80, 60};
};


class PreMash_TempDown : Button {
public:
    PreMash_TempDown(Utils * u_ptr) : Button(u_ptr) {};
    void drawButton();
    void checkIfAreaTouched(TS_Point&);
private:
    BoxCoords coords = {30, 50, 80, 60}; 
};


class PreMash_TimeUp : Button {
public:
    PreMash_TimeUp(Utils * u_ptr) : Button(u_ptr) {};
    void drawButton();
    void checkIfAreaTouched(TS_Point&);
private:
    BoxCoords coords = {140, 150, 80, 60};
};

class PreMash_TimeDown : Button {
public:
    PreMash_TimeDown(Utils * u_ptr) : Button(u_ptr) {};
    void drawButton();
    void checkIfAreaTouched(TS_Point&);
private:
    BoxCoords coords = {30, 150, 80, 60};
};

class PreMash_Begin : Button {
public:
    PreMash_Begin(Utils * u_ptr) : Button(u_ptr) {};
    void drawButton();
    void checkIfAreaTouched(TS_Point&);
private:
    BoxCoords coords = {30, 230, 160, 70};
};

class Display
{
public:

    Display(){};
    
    Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
    Adafruit_FT6206 ctp = Adafruit_FT6206();
    
    void init() {
        tft.begin();
        tft.fillScreen(Bg);
        
        // *** Capacitive Touch Setup ***
        if(!ctp.begin()) {
            Serial.println("Unable to initialize ctp!");
            tft.print("Cap Touch Init Failed!");
        }
    }


	~Display(){};
};

extern Display disp;
extern Utils * utils_Ptr;

#endif // Display_h
