#ifndef BrewStates_h
#define BrewStates_h

#include "Display.h"
#include "Utils.h"

class BrewState {
public:
    BrewState(){};
    virtual void dispInit();
    virtual void dispUpdate();
    // virtual void touchControl();   // TODO
};

class PreMash : BrewState {
public:
    PreMash(){};
    void dispInit();
    void dispUpdate();
};

class Mash : BrewState {
public:
    Mash(){};
    void dispInit();
    void dispUpdate();
};


// extern PreMash preMashState;
// extern Mash mashState;

#endif // ifndef BrewStates_h
