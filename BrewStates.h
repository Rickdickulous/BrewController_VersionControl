#ifndef BrewStates_h
#define BrewStates_h

#include "Display.h"
#include "Utils.h"

class BrewState {
public:
    BrewState(){};
    virtual void dispInit();
    virtual void dispUpdate();
    virtual bool touchControl();
};

class PreMash : BrewState {
public:
    PreMash(Utils * const utils_Ptr) : utils_Ptr(utils_Ptr) {};
    void dispInit();
    void dispUpdate();
    bool touchControl();

private:
    Utils * const utils_Ptr;
};

class Mash : BrewState {
public:
    Mash(Utils * const utils_Ptr) : utils_Ptr(utils_Ptr) {};
    void dispInit();
    void dispUpdate();
    bool touchControl();

private:
    Utils * const utils_Ptr;
};


// extern PreMash preMashState;
// extern Mash mashState;

#endif // ifndef BrewStates_h
