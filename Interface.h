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
    Display disp = Display();

   PreMash preMashState = PreMash();
   Mash mashState = Mash();

private:
    void * StateMap[MAX_STATES] = { &preMashState,
                                    &mashState
                                  };

};



#endif // Interface_h
