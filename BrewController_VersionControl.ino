// Dick Bilt Libraries
#include "Utils.h"
#include "Display.h"


// display libraries
#include "SPI.h"
#include "Adafruit_GFX.h"

Utils utils = Utils();
Display disp = Display();


// variable declarations
int thermistorBufferIndex = 0;


// Timing & Timers variables
unsigned int const UpdateInterval_long = 1500;
unsigned int const UpdateInterval_short = 250;
unsigned long prevMillis_short = 0;
unsigned long prevMillis_long = 0;
unsigned long currentMillis = 0;


// debug log
bool const debug = true;
void printDebug(void)
{
    if (debug)
    {
      STR(utils.currentTemp_f);
      STR(utils.currentTempSetpoint_f);
      STR(utils.valveSetpoint);
    }
}


void cacheThermistorReadings()
{
    if (thermistorBufferIndex == (utils.ThermistorBufferSize - 1) )
    { 
        thermistorBufferIndex = 0;
    }

    int thermistorReading_Vcounts = analogRead(THERMISTOR_PIN);    // read the thermistor pin
    utils.thermistorBuffer[thermistorBufferIndex] = thermistorReading_Vcounts;

    thermistorBufferIndex++;
}


void everythingTempControl()
{ 
    // get current probe temp degrees F
    utils.calcProbeTemp();
    
    //
    // get valve setpoint based on current probe temp
    //
    utils.calcValveSetpoint();  // determines how big flame should be (analogWrite takes int)

    

    analogWrite(VALVE_PIN, utils.valveSetpoint);  // set valve open amount
}

void setup()
{
    pinMode(VALVE_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);

    disp.init(utils);

    //initialize thermistor buffer
    int initReading = analogRead(THERMISTOR_PIN);
    for(int i=0; i<utils.ThermistorBufferSize; i++)
    {
        utils.thermistorBuffer[i] =   initReading;
    }

    Serial.begin(9600);  // begin serial communication
}

void loop()
{
    currentMillis = millis();
    if ( (currentMillis - prevMillis_short) >= UpdateInterval_short )
    {
        cacheThermistorReadings();
        utils.handleFlameSensor();
        
        if ( (currentMillis - prevMillis_long) >= UpdateInterval_long )
        {
            everythingTempControl();  // must come before displaying!
            disp.printOnScreen(utils);

            if (debug)
            {
                printDebug();
            }
            prevMillis_long = currentMillis;
        }  // long
        prevMillis_short = currentMillis;
    }  // short
    
    disp.touchControl(utils);
}


