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
    Button(Adafruit_ILI9341 * tft_p, Adafruit_FT6206 * ctp_p) {tft_ptr = tft_p;
                                                               ctp_ptr = ctp_p;};
    virtual void checkIfAreaTouched(TS_Point&) = 0;  // executes sideEffect function
    virtual void drawButton() = 0;
    Adafruit_ILI9341 * tft_ptr;
    Adafruit_FT6206 * ctp_ptr;
};

class ControllerUp : Button {
public:
      ControllerUp(Adafruit_ILI9341 * tft_p, Adafruit_FT6206 * ctp_p) : Button(tft_p,ctp_p) {};
      void drawButton();
      void checkIfAreaTouched(TS_Point&);
      ~ControllerUp() {};
      
private:               // x,  y,  w,  h
    BoxCoords coords = {140, 50, 80, 60};
};


class ControllerDown : Button {
public:
    ControllerDown(Adafruit_ILI9341 * tft_p, Adafruit_FT6206 * ctp_p) : Button(tft_p,ctp_p) {};
    void drawButton();
    void checkIfAreaTouched(TS_Point&);
    ~ControllerDown() {};
private:
    BoxCoords coords = {30, 50, 80, 60}; 
};


class TimeUp : Button {
public:
    TimeUp(Adafruit_ILI9341 * tft_p, Adafruit_FT6206 * ctp_p) : Button(tft_p,ctp_p) {};
    void drawButton();
    void checkIfAreaTouched(TS_Point&);
    ~TimeUp() {Serial.println("Destroy TU");};
private:
    BoxCoords coords = {140, 150, 80, 60};
};

class TimeDown : Button {
public:
    TimeDown(Adafruit_ILI9341 * tft_p, Adafruit_FT6206 * ctp_p) : Button(tft_p,ctp_p) {};
    void drawButton();
    void checkIfAreaTouched(TS_Point&);
    ~TimeDown() {};
private:
    BoxCoords coords = {30, 150, 80, 60};
};

class StartTimer : Button {
public:
    StartTimer(Adafruit_ILI9341 * tft_p, Adafruit_FT6206 * ctp_p) : Button(tft_p,ctp_p){};
    void drawButton();
    void checkIfAreaTouched(TS_Point&);
    ~StartTimer(){};
private:
    BoxCoords coords = {30, 230, 160, 70};
};

class Display
{
public:

    Display(){};
    
    Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
    Adafruit_FT6206 ctp = Adafruit_FT6206();
    
    void init();
    void dispUpdate();
    bool touchControl(TS_Point&);

    ControllerUp contUp = ControllerUp(&tft, &ctp);
    ControllerDown contDown = ControllerDown(&tft, &ctp);
    TimeUp timeUp = TimeUp(&tft, &ctp);
    TimeDown timeDown = TimeDown(&tft, &ctp);
    StartTimer startTimer = StartTimer(&tft, &ctp);
    static int const NumButtons = 5;  // must equal number of buttons in buttons[] below
    void * buttons[NumButtons] = { &contUp, &contDown, &timeUp, &timeDown, &startTimer };


	~Display(){};

};

#endif // Display_h
