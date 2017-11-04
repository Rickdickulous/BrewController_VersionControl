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
# define SCREEN_HEIGHT_PIXELS 320

void Display::init(void)
{
	  // Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
    tft.begin();
    drawSquare();
    printOnScreen();
}

void Display::drawSquare(void)
{
    // yield() may be necessary to prevent watchdog timeouts on blocking calls which cause hardware resets
    tft.fillScreen(BLUE);
    tft.fillRect(SCREEN_WIDTH_PIXELS/2, SCREEN_HEIGHT_PIXELS/2, 50, 75, YELLOW);
    tft.drawRect(SCREEN_WIDTH_PIXELS/4, SCREEN_HEIGHT_PIXELS/4, 20, 20, CYAN);  
}

void Display::printOnScreen(void)
{
  tft.setCursor(10, 50);
  tft.setTextColor(ILI9341_RED);    tft.setTextSize(2);
  tft.print("Hello World!");
  tft.println("Now");
}
