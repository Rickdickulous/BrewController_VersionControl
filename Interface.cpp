#include "Interface.h"


// Timing & Timers variables
unsigned int const UpdateInterval_long = 1500;
unsigned int const UpdateInterval_short = 250;
unsigned long prevMillis_short = 0;
unsigned long prevMillis_long = 0;
unsigned long currentMillis = 0;


void Interface::init() {
    BrewState * bs = static_cast<BrewState*>(StateMap[utils.currentState]);
    bs->dispInit();
  
    disp.init();
    disp.initState(utils);
    
    utils.currentState = PRE_MASH;
    utils.init();
}


void Interface::brewsistantManager() {
    manageTimedServices();
    
    if (utils.currentState != utils.prevState)
    {
        disp.initState(utils);  
    }
}

void Interface::manageTimedServices() {
    currentMillis = millis();
    BrewState * bs = static_cast<BrewState*>(StateMap[utils.currentState]);
    
    if ( (currentMillis - prevMillis_short) >= UpdateInterval_short )
    {
        utils.cacheThermistorReadings();
        utils.handleFlameSensor();
        
        if ( (currentMillis - prevMillis_long) >= UpdateInterval_long )
        {
            utils.everythingTempControl();  // must come before displaying!

            bs->dispUpdate();

            //disp.printOnScreen(utils);

            if (utils.debug)
            {
                utils.printDebug();
            }
            prevMillis_long = currentMillis;
        }  // long
        prevMillis_short = currentMillis;
    }  // short

    if ( bs->touchControl() ) {
        bs->dispUpdate();
        delay(100);
    }
    // disp.touchControl(utils);  
}
