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




#define SCREEN_WIDTH_PIXELS 240
#define SCREEN_HEIGHT_PIXELS 320


int const Bg = DARKGREY;     // Background color
int const Tc = GREENYELLOW;  // text color

double prevActualTemp = 0.0;
int prevTempSetpoint = 0;
int prevValveSetpoint = 0;

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

    // *** Display Current Water Temp ***
    tft.setCursor(0, 75);
    tft.print("Actual Temp: ");

    // *** Display Valve Setpoint ***
    tft.setCursor(0, 125);
    tft.print("Valve Setpoint: ");

    tft.drawRect(30, 175, 75, 100, BLACK);
    tft.drawRect(140, 175, 75, 100, BLACK);

    tft.setCursor(60, 210);
    tft.setTextColor(BLUE);
    tft.setTextSize(3);
    tft.print("-");

    tft.setCursor(170, 210);
    tft.setTextColor(RED);
    tft.print("+");
    


    // *** Capacitive Touch Setup ***
    if(!ctp.begin())
    {
        Serial.println("Unable to initialize ctp!");
    }

    tft.setTextSize(2);  // reset text size for live updates
}

void Display::printOnScreen(Utils& utils)
{
    // *** Display Target Temp *** 
    
    if (prevTempSetpoint != 0)
    {
        tft.setCursor(150, 25);
        tft.setTextColor(Bg);
        tft.print(prevTempSetpoint);  
    }
    tft.setCursor(150, 25);
    tft.setTextColor(Tc);
    tft.print(utils.currentTempSetpoint_f);
    prevTempSetpoint = utils.currentTempSetpoint_f;

    // *** Display Current Water Temp ***
    
    if (prevActualTemp != 0)
    {
        tft.setCursor(150, 75);
        tft.setTextColor(Bg);
        tft.print(prevActualTemp);
    }
    tft.setCursor(150, 75);
    tft.setTextColor(Tc);
    tft.print(utils.currentTemp_f);
    prevActualTemp = utils.currentTemp_f;

    // *** Display Valve Setpoint ***
    if (prevValveSetpoint != 0)
    {
        tft.setCursor(185, 125);
        tft.setTextColor(Bg);
        tft.print(prevValveSetpoint);
    }
    tft.setCursor(185, 125);
    tft.setTextColor(Tc);
    tft.println(utils.valveSetpoint);
    prevValveSetpoint = utils.valveSetpoint;
}

void Display::touchControl(Utils& utils)
{
    if (!ctp.touched())
    {
        return;
    }

    TS_Point p = ctp.getPoint();
    p.x = map(p.x, 0, 240, 240, 0);
    p.y = map(p.y, 0, 320, 320, 0);
    //p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    //p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

    Serial.print("p.x = ");
    Serial.println(p.x);
    Serial.print("p.y = ");
    Serial.println(p.y);

    // is button press within +/- button y range?
    if ( 165 <= p.y <= 265 )
    {
        // yes! Based on x value, is it an up or down press?
        if ( (30 <= p.x) && ( p.x <= 90) )
        {
            utils.currentTempSetpoint_f--;  
        }
        else if ( (130 <= p.x) && (p.x <= 210) )
        {
            utils.currentTempSetpoint_f++;  
        }

        // update display after button press
        printOnScreen(utils);
        delay(100);
        
    }
    else
    {
        return;
    }    
}
