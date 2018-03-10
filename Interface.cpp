#include "Interface.h"


// Timing & Timers variables
unsigned int const UpdateInterval_long = 1500;
unsigned int const UpdateInterval_short = 250;
unsigned long prevMillis_short = 0;
unsigned long prevMillis_long = 0;
unsigned long currentMillis = 0;


void Interface::init() {
    BrewState * brewState_ptr = static_cast<BrewState*>(StateMap[utils.currentState]);
    brewState_ptr->dispInit();
        
    utils.init();
}


void Interface::brewsistantManager() {
    manageTimedServices();

    BrewState * brewState_ptr = static_cast<BrewState*>(StateMap[utils.currentState]);
    if (utils.currentState != utils.prevState) {
      utils.prevState = utils.currentState;
        brewState_ptr->dispInit();
    }
}

void Interface::manageTimedServices() {
    currentMillis = millis();
    BrewState * brewState_ptr = static_cast<BrewState*>(StateMap[utils.currentState]);  // TBD: What is the difference between static_cast here and just (BrewState*) cast??
    
    if ( (currentMillis - prevMillis_short) >= UpdateInterval_short ) {
        utils.cacheThermistorReadings();
        utils.handleFlameSensor();
        
        if ( (currentMillis - prevMillis_long) >= UpdateInterval_long ) {
            utils.everythingTempControl();  // must come before displaying!

            brewState_ptr->dispUpdate();

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
    
        brewState_ptr->touchControl(p);
        brewState_ptr->dispUpdate();
        delay(100);
    }

}

