#ifndef BrewStates_h
#define BrewStates_h

#include "Display.h"
#include "Utils.h"

class BrewState {
public:
    BrewState(){};
    virtual void dispInit() = 0;
    virtual void dispUpdate() = 0;
    virtual bool touchControl(TS_Point&) = 0;
};

class PreMash : BrewState {
public:
    PreMash(Utils * const utils_Ptr) : utils_Ptr(utils_Ptr) {};
    void dispInit();
    void dispUpdate();
    bool touchControl(TS_Point&);

private:
    PreMash_TempUp tempUp = PreMash_TempUp(utils_Ptr);
    PreMash_TempDown tempDown = PreMash_TempDown(utils_Ptr);
    PreMash_TimeUp timeUp = PreMash_TimeUp(utils_Ptr);
    PreMash_TimeDown timeDown = PreMash_TimeDown(utils_Ptr);
    static int const NumButtons = 4;  // must equal number of buttons in buttons[]
    void * buttons[NumButtons] = { &tempUp, &tempDown, &timeUp, &timeDown };
    
    // create array of pointers to button objects
    Utils * const utils_Ptr;
};

/* ***********
 *  TODO: Make a template class for mash states since they should all have identical interfaces
 * *************/


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
