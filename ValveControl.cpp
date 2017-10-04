#include "ValveControl.h"

ValveControl::ValveControl(void) {}

int ValveControl::calcSetpoint(float currentTemp, int currentSetpoint)
{
    /* *********************
    NOTE: Could also base flame output based on percentage
          of difference between setPoint and current Temp.
    ********************* */

    float diff = (float) currentSetpoint - currentTemp;

    int retVal;

    if (diff < 3)
        {retVal = Low;}
    else if (diff < 6)
        {retVal = MedLow;}
    else if (diff < 8)
        {retVal = Med;}
    else if (diff < 10)
        {retVal = MedHigh;}
    else
        {retVal = High;}

    return retVal;
}

/*  const int Low = 150;
    const int MedLow = 175;
    const int Med = 200;
    const int MedHigh = 225;
    const int High = 255;       */


ValveControl::~ValveControl(void) {}
