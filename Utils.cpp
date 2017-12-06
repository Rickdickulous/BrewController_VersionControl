#include "Utils.h"

extern bool debug;


float Utils::convertInputToTemp_f(float& thermistorReading_counts)
{
    Rt = R1 / (1024/thermistorReading_counts - 1);  // cast thermistorReading_counts to float to prevent rounding errors
    float temp_C = (-26.65) * log(Rt) + 271.11;
    currentTemp_f = temp_C * 1.8 + 32;
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

void Utils::handleFlameSensor(int& flameSensorInput)
{
  if (flameSensorInput > 900)
  {
    //Serial.println("NO FLAME, WAYNE!");
  }
  else
  {
    //Serial.println("FLAME ON, GARTH!");
  }
}

void Utils::makeNoise(int selector)
{
    switch(selector)
    {
    case 1:
        {
            int melody[] = {NOTE_C5, NOTE_G5, NOTE_A4, NOTE_B5, NOTE_G5, NOTE_A6, NOTE_B5, NOTE_D5};

            for (int thisNote = 0; thisNote < 8; thisNote++)
            {
              // pin8 output the voice, every scale is 0.5 sencond
              tone(8, melody[thisNote], 500);
              delay(500);
            }
        }  // case 1
    }  // switch(selector)
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
