#include "Utils.h"

extern bool debug;


float Utils::convertInputToTemp_f(int& thermistorReading_counts)
{
    Rt = R1 / (1024/thermistorReading_counts - 1);
    float temp_C = (-26.65) * log(Rt) + 271.11;
    float temp_F = temp_C * 1.8 + 32;
    return temp_F;
}


int Utils::getFlameInput(int& ticks)
{
    int retVal = 0;
    incomingByte = 0;
    if (debug)
    {
        Serial.print("ticks = ");
        Serial.println(ticks);
    }

    Serial.println("Enter integer between 100 - 255 to set flame output:");
    while (Serial.available() == 0) {}

    while( Serial.available() > 0 )
    {
        incomingByte += Serial.read();
    }    // stays here until 1 or more bytes are pushed to the receive buffer

    if (incomingByte > 0)
    {
        Serial.print("Received: ");
        Serial.println(incomingByte);
    }

    // TODO: Enter a - z for flame level. a = 100, z = 250

    ticks += 100;
}




/*
float TempController::convertInputToTemp_C(float Vcounts)
{
    Rt = R1 / (1024/Vcounts - 1);
    float temp_C = (-26.65) * log(Rt) + 271.11;
    return temp_C;
}


float TempController::cToF(float temp_c)
{
    return temp_c * 1.8 + 32;
}
*/
