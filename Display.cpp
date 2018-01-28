#include "Display.h"


void Display::init() {
    tft.begin();
    tft.fillScreen(Bg);
    
    // *** Capacitive Touch Setup ***
    if(!ctp.begin())
    {
        Serial.println("Unable to initialize ctp!");
        tft.print("Cap Touch Init Failed!");
    }

}


void Display::touchControl(Utils& utils)
{
    
}
