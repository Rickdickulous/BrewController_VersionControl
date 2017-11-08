#include "Display.h"

/*
// Color definitions
#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0 
#define WHITE    0xFFFF
*/

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


#define SCREEN_WIDTH_PIXELS 240
#define SCREEN_HEIGHT_PIXELS 320


int const Bg = DARKGREY;     // Background color
int const Tc = GREENYELLOW;  // text color

double prevActualTemp = 0.0;

void Display::init(Utils& utils)
{
	  // Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
    tft.begin();
    tft.fillScreen(Bg);
    tft.setTextColor(Tc);
    tft.setTextSize(2);

    // *** Display Target Temp *** 
    tft.setCursor(0, 25);
    tft.print("Target Temp: ");
    tft.print(utils.CurrentTempSetpoint_f);

    // *** Display Current Water Temp ***
    tft.setCursor(0, 75);
    tft.print("Actual Temp: ");

    // *** Display Valve Setpoint ***
    tft.setCursor(0, 125);
    tft.print("Valve Setpoint = ");

    // drawSquare();
}


void Display::drawSquare(void)
{
    
    tft.fillRect(SCREEN_WIDTH_PIXELS/2, SCREEN_HEIGHT_PIXELS/2, 50, 75, YELLOW);
    tft.drawRect(SCREEN_WIDTH_PIXELS/4, SCREEN_HEIGHT_PIXELS/4, 20, 20, CYAN);  
}


void Display::test(void)
{
  while(1)
  {
    tft.setCursor(10,10);
    tft.setTextColor(Tc);
    tft.print("test");
    delay(1000);
    tft.setCursor(10,10);
    tft.setTextColor(Bg);
    tft.print("test");
    delay(1000);
    Serial.println("Round...");
  }  
}


void Display::printOnScreen(Utils& utils)
{
    // *** Display Target Temp *** 
    /*tft.setCursor(150, 50);
    tft.setTextColor(Bg);
    tft.println("     ");
    tft.setTextColor(Tc);
    tft.println(utils.CurrentTempSetpoint_f);*/

    // *** Display Current Water Temp ***
    tft.setCursor(150, 75);
    if (prevActualTemp != 0)
    {
        tft.setTextColor(Bg);
        tft.print(prevActualTemp);
    }
    tft.setCursor(150, 75);
    tft.setTextColor(Tc);
    tft.print(utils.currentTemp_f);
    prevActualTemp = utils.currentTemp_f;



    // *** Display Valve Setpoint ***
    tft.setCursor(100, 150);
    tft.println(utils.valveSetpoint);
}
