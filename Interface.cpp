#include "Interface.h"

// Timing & Timers variables
unsigned int const UpdateInterval_long = 1500;
unsigned int const UpdateInterval_short = 250;
unsigned long prevMillis_short = 0;
unsigned long prevMillis_long = 0;
unsigned long currentMillis = 0;


void Interface::init() {
    utils.init();
    disp.init();
}


void Interface::brewsistantManager() {
    manageTimedServices();
    
}

void Interface::manageTimedServices() {
    currentMillis = millis();
    
    if ( (currentMillis - prevMillis_short) >= UpdateInterval_short ) {
        utils.cacheThermistorReadings();
        utils.handleFlameSensor();
        
        if ( (currentMillis - prevMillis_long) >= UpdateInterval_long ) {
            utils.everythingTempControl();  // must come before displaying!

            disp.dispUpdate();

            Serial.println(utils.currentTempSetpoint_f);

            

            if (utils.debug)
            {
                utils.printDebug();
            }
            prevMillis_long = currentMillis;
        }  // long
        prevMillis_short = currentMillis;
    }  // short

    if (disp.ctp.touched()) {
        TS_Point p = disp.ctp.getPoint();
        p.x = map(p.x, 0, 240, 240, 0);  // convert to numbers that make sense on our screen
        p.y = map(p.y, 0, 320, 320, 0);

        Serial.print("p.x = ");
        Serial.println(p.x);
        Serial.print("p.y = ");
        Serial.println(p.y);
    
        disp.touchControl(p);
        disp.dispUpdate();
        delay(100);
    }

}

