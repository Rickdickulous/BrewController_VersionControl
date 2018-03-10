#include "Utils.h"

int currentTempSetpoint_f;
int timer_sec;
Utils utils;

void Utils::printDebug(void) {
    if (debug) {
      STR(currentTemp_f);
      STR(currentTempSetpoint_f);
      STR(valveSetpoint);
    }
}


void Utils::init() {currentTempSetpoint_f = 150;
                    timer_sec = 30;} 


void Utils::calcProbeTemp(void)
{
    // Get Average
    float sum = 0;
    for (int i=0; i<ThermistorBufferSize; i++) {
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
  if (flameSensorInput > 900) {
    //Serial.println("NO FLAME, WAYNE!");
  }
  else {
    //Serial.println("FLAME ON, GARTH!");
  }
}


void Utils::cacheThermistorReadings()
{
    if (thermistorBufferIndex == (ThermistorBufferSize - 1) ) { 
        thermistorBufferIndex = 0;
    }

    int thermistorReading_Vcounts = analogRead(THERMISTOR_PIN);    // read the thermistor pin
    thermistorBuffer[thermistorBufferIndex] = thermistorReading_Vcounts;

    thermistorBufferIndex++;
}


void Utils::everythingTempControl()
{ 
    // get current probe temp degrees F
    calcProbeTemp();
    
    //
    // get valve setpoint based on current probe temp
    //
    calcValveSetpoint();  // determines how big flame should be (analogWrite takes int)

    

    analogWrite(VALVE_PIN, valveSetpoint);  // set valve open amount
}


void Utils::makeNoise(int selector)
{
    switch(selector) {
        case 1: {
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

