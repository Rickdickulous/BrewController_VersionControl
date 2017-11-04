#ifndef Utils_h
#define Utils_h

#include "Arduino.h"

class Utils
{
public:
    Utils(){};

    float convertInputToTemp_f(int&);
    int getFlameInput(int&);

    int calcValveSetpoint(float& currentTemp_f, int const& CurrentSetpoint_f)
    {
        int retVal;
        /* *********************
        NOTE: Could also base flame output based on percentage
              of difference between setPoint and current Temp.
        ********************* */
        float diff = (float) CurrentSetpoint_f - currentTemp_f;
    
        if (diff < 2)
            {retVal = 135;}
        else if (diff < 5)
            {retVal = 160;}
        else if (diff < 10)
            {retVal = 200;}
        else if (diff < 15)
            {retVal = 220;}
        else
            {retVal = 255;}
    
        return retVal;
    }

    ~Utils(){};
private:
    float Rt = 0.0;
    const int R1 = 10180;
    int incomingByte;



    //float Vin = 4.9;                          // dave's notes
    //float ADC_VoltPerCount = 4.9/1024.0;      // dave's notes
    //Temp = 0.3626 * Rt + 101.33               // dave's notes
    //y = -26.65ln(Rt) + 271.11                 // dave's notes

    //y = 2.7552x - 279.15                      // dave's notes
};


#endif // Utils_h
