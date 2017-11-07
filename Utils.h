#ifndef Utils_h
#define Utils_h

#include "Arduino.h"
#include "pitches.h"

#define STR(x) Serial.print(#x); Serial.print(" = "); Serial.println(x);
#define RICK_MIN 135
#define JIM_MIN 132

class Utils
{
public:
    Utils(){};

    double currentTemp_f;
    int valveSetpoint;
    int const CurrentTempSetpoint_f = 177;

    float convertInputToTemp_f(float&);
    int getFlameInput(int&);
    void makeNoise(void);
    void handleFlameSensor(int&);

    bool noiseMade = false;
    
    int calcValveSetpoint()
    {
        int retVal;
        float diff = (float) CurrentTempSetpoint_f - currentTemp_f;
    
        if (diff < 2)
            {valveSetpoint = JIM_MIN; 
              if (false == noiseMade)
              {makeNoise(); noiseMade = true;}
            }  
        else if (diff < 4)
            {valveSetpoint = 180;}
        else if (diff < 7)
            {valveSetpoint = 200;}
        else if (diff < 10)
            {valveSetpoint = 225;}
        else
            {valveSetpoint = 255;}
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
