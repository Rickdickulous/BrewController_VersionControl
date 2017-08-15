#ifndef TempController_h
#define TempController_h

#include "Arduino.h"


class TempController
{
public:
    TempController(void);
    float temperature = 0.0;
    float Rt = 0.0;

    //float Vin = 4.9;                          // dave's notes
    //float ADC_VoltPerCount = 4.9/1024.0;      // dave's notes
    //Temp = 0.3626 * Rt + 101.33               // dave's notes
    //y = -26.65ln(Rt) + 271.11                 // dave's notes

    //y = 2.7552x - 279.15                      // dave's notes
    float convertInputToTemp_F(float);
    float convertInputToTemp_C(float);
    float cToF(float);
    ~TempController(void);

private:

    const int R1 = 10180;

};
#endif // TempController
