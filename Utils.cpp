#include "Utils.h"

extern bool debug;


float Utils::convertInputToTemp_f(int& thermistorReading_counts)
{
    Rt = R1 / (1024/(float)thermistorReading_counts - 1);  // cast thermistorReading_counts to float to prevent rounding errors
    float temp_C = (-26.65) * log(Rt) + 271.11;
    return temp_C * 1.8 + 32;
}


void Utils::calcProbeTemp(void)
{
    int sum = 0;
    for (int i=0; i<ThermistorBufferSize; i++)
    {
        sum += thermistorBuffer[i];
    }

    currentTemp_f = convertInputToTemp_f(sum);
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
