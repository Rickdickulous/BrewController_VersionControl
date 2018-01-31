#ifndef Interface_h
#define Interface_h

#include "Arduino.h"
#include "Display.h"
#include "Utils.h"
#include "BrewStates.h"


class Interface
{
public:
    Interface() {};  // constructor
    void init();

    void brewsistantManager();
    void manageTimedServices();

    Utils utils = Utils();

private:
    PreMash preMashState = PreMash(&utils);
    //Mash mashState = Mash(&utils);
    
    void * StateMap[MAX_STATES] = { &preMashState,
                                    //&mashState
                                  };
};


#endif // Interface_h
