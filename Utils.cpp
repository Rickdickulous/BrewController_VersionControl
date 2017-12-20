#include "Utils.h"

extern bool debug;


void Utils::calcProbeTemp(void)
{
    // Get Average
    float sum = 0;
    for (int i=0; i<ThermistorBufferSize; i++)
    {
        sum += thermistorBuffer[i];
    }
    float avg = sum/ThermistorBufferSize;

    // convert to degrees F
    float Rt = 10180 / (1024/avg - 1);  // cast thermistorReading_counts to float to prevent rounding errors
    float temp_C = (-26.65) * log(Rt) + 271.11;
    currentTemp_f = temp_C * 1.8 + 32;
}


void Utils::handleFlameSensor(void)
{
    int flameSensorInput = analogRead(FLAME_SENSOR_PIN);
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
              tone(BUZZER_PIN, melody[thisNote], 500);
              delay(500);
            }
        }  // case 1
    }  // switch(selector)
}
