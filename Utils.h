#ifndef Utils_h
#define Utils_h

#include "Arduino.h"
#include "pitches.h"

#define STR(x) Serial.print(#x); Serial.print(" = "); Serial.println(x);
#define RICK_MIN 135
#define JIM_MIN 132

#define ALARM1
#define ALARM2
#define MELODY1
#define MELODY2



class Utils
{
public:
    Utils(){};

    double currentTemp_f;
    int valveSetpoint;
    int currentTempSetpoint_f = 150;

    float convertInputToTemp_f(float&);
    int getFlameInput(int&);
    void makeNoise(int);
    void handleFlameSensor(int&);

    bool noiseMade = false;

    int calcValveSetpoint()
    {
        int retVal;
        float diff = (float) currentTempSetpoint_f - currentTemp_f;

        if (diff < 2)
            {valveSetpoint = JIM_MIN;
              if (false == noiseMade)
              {makeNoise(1); noiseMade = true;}
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
};


#endif // Utils_h
