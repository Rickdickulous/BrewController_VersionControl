#include "Display.h"


void Display::init() {
    disp.tft.begin();
    disp.tft.fillScreen(Bg);
    
    // *** Capacitive Touch Setup ***
    if(!disp.ctp.begin())
    {
        Serial.println("Unable to initialize ctp!");
        disp.tft.print("Cap Touch Init Failed!");
    }

}


void Display::touchControl(Utils& utils)
{
    
}
