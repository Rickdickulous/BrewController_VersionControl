#ifndef Interface_h
#define Interface_h

#include "Arduino.h"
#include "Display.h"
#include "Utils.h"
#include "global.h"

class Interface
{
public:
    Interface() {};  // constructor
    void init();

    void brewsistantManager();

    void manageTimedServices();

    Utils utils = Utils();
    Display disp = Display();
    
    
};




#endif // Interface_h
