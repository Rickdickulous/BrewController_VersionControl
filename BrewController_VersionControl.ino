// Dick Bilt Libraries
#include "Utils.h"
#include "Display.h"


// display libraries
#include "SPI.h"
#include "Adafruit_GFX.h"

Utils utils = Utils();
Display disp = Display();


// variable declarations
float thermistorReading_Vcounts = 0.0;
int thermistorBufferIndex = 0;
int flameSensorReading_counts = 1000;  // >900 means flame is on, so initialize to big number


// Timing & Timers variables
unsigned int const UpdateInterval_long = 1500;
unsigned int const UpdateInterval_short = 100;
unsigned long prevMillis = 0;
unsigned long currentMillis = 0;


// Pin Declarations
int const ValvePin = 6;
int const ThermistorPin = 0;
int const BuzzerPin = 8;
int const FlameSensorPin = 1;


// ** Override valve open setpoint **
int const ValveSetpointOverride = 0;  // Set to 0 to disable


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

    thermistorReading_Vcounts = analogRead(ThermistorPin);    // read the thermistor pin
    utils.thermistorBuffer[thermistorBufferIndex] = thermistorReading_Vcounts;

    thermistorBufferIndex++;
}

void everythingTempControl()
{ 
    // get current probe temp degrees F
    utils.calcProbeTemp();
    
    // utils.currentTemp_f += 12;  // IMPORTANT! - Subtract 6 here to make temperature probe accurate at 155F.

    //
    // get valve setpoint based on current probe temp
    //
    utils.calcValveSetpoint();  // determines how big flame should be (analogWrite takes int)

    flameSensorReading_counts = analogRead(FlameSensorPin);
    utils.handleFlameSensor(flameSensorReading_counts);

    if (ValveSetpointOverride)
    {
      Serial.println("Overriding valve setpoint!");
      utils.valveSetpoint = ValveSetpointOverride;
    }
    if (debug)
    {
      printDebug();
    }

    analogWrite(ValvePin, utils.valveSetpoint);  // set valve open amount
}

void setup()
{
    pinMode(ValvePin, OUTPUT);
    pinMode(BuzzerPin, OUTPUT);

    disp.init(utils);

    Serial.begin(9600);  // begin serial communication
}

void loop()
{
    currentMillis = millis();
    if ( (currentMillis - prevMillis) >= UpdateInterval_short )
    {
        cacheThermistorReadings();
        
        if ( (currentMillis - prevMillis) >= UpdateInterval_long )
        {
            everythingTempControl();  // must come before displaying!
            disp.printOnScreen(utils);  
        }
        
        prevMillis = currentMillis;
    }
    
    disp.touchControl(utils);
}


