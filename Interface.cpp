#include "Interface.h"


// Timing & Timers variables
unsigned int const UpdateInterval_long = 1500;
unsigned int const UpdateInterval_short = 250;
unsigned long prevMillis_short = 0;
unsigned long prevMillis_long = 0;
unsigned long currentMillis = 0;


void Interface::init() {
    disp.init(utils);
}


void Interface::brewsistantManager() {
    manageTimedServices();
}

void Interface::manageTimedServices() {
    currentMillis = millis();
    if ( (currentMillis - prevMillis_short) >= UpdateInterval_short )
    {
        utils.cacheThermistorReadings();
        utils.handleFlameSensor();
        
        if ( (currentMillis - prevMillis_long) >= UpdateInterval_long )
        {
            utils.everythingTempControl();  // must come before displaying!
            disp.printOnScreen(utils);

            if (utils.debug)
            {
                utils.printDebug();
            }
            prevMillis_long = currentMillis;
        }  // long
        prevMillis_short = currentMillis;
    }  // short
    
    disp.touchControl(utils);  
}

