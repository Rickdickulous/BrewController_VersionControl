#ifndef Utils_h
#define Utils_h

#include "Arduino.h"
#include "pitches.h"

#define STR(x) Serial.print(#x); Serial.print(" = "); Serial.println(x);
#define RICK_MIN 135
#define JIM_MIN 132

#define VALVE_PIN 6
#define THERMISTOR_PIN 0
#define FLAME_SENSOR_PIN 1
#define BUZZER_PIN 8

enum States {
    INIT,
    PRE_MASH,
    MASH,
    PRE_BOIL,
    BOIL
};


class Utils
{
public:
    Utils(){};

    int currentState;
    int prevState;

    bool const debug = true;
    int thermistorBufferIndex = 0;
    double currentTemp_f;
    int valveSetpoint;
    static int const ThermistorBufferSize = 20;
    int currentTempSetpoint_f = 150;
    int thermistorBuffer[ThermistorBufferSize];  // circular buffer for thermistor readings

    void calcProbeTemp(void);
    void makeNoise(int);
    void handleFlameSensor(void);
    void cacheThermistorReadings();
    void everythingTempControl();
    void printDebug();

    bool noiseMade = false;

    int calcValveSetpoint()
    {
        int retVal;
        float diff = (float) currentTempSetpoint_f - currentTemp_f;

        if (diff < 1.25)
            {valveSetpoint = JIM_MIN;
              //if (false == noiseMade)
              //{makeNoise(1); noiseMade = true;}
            }
        else if (diff < 2)
            {valveSetpoint = 145;}
        else if (diff < 3)
            {valveSetpoint = 160;}
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

};


#endif // Utils_h
