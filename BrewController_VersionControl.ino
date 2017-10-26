#include "Utils.h"
Utils utils = Utils();


// variable declarations
int thermistorReading_Vcounts = 0;
float currentTemp_f = 0.0;
int valveSetpoint;
unsigned long ticks_100ms = 0;  // print using lu


// CPin Declarations
int const ValvePin = 6;
int const ThermistorPin = 0;
int const buzzerPin = 8;


// ** Override valve open setpoint **
int const CurrentTempSetpoint_f = 208;
int const ValveSetpointOverride = 0;  // Set to 0 to disable


// debug log  ||
const bool debug = true;
void printDebug(void)
{
    if (debug)
    {
        Serial.print("currentTemp (F) = ");
        Serial.println(currentTemp_f);
        Serial.print("curret setpoint = ");
        Serial.println(CurrentTempSetpoint_f);
        Serial.print("valveSetpoint = ");
        Serial.println(valveSetpoint);
    }
}


void setup()
{
    pinMode(ValvePin, OUTPUT);
    pinMode(buzzerPin, OUTPUT);
    
    Serial.begin(9600);  // begin serial communication

    /*
    Serial.println("Hit a key to start");
    while( Serial.available() == 0 ) {}  // stays here until 1 or more bytes are pushed to the receive buffer
    Serial.flush();  // waits for data to finishing transmitting to the serial buffer before moving on
    */
}

void loop()
{
    // valveSetpoint = utils.getFlameInput(ticks_100ms);

    //
    // get current probe temp in degrees F
    //
    thermistorReading_Vcounts = analogRead(ThermistorPin);    // read the thermistor pin
    currentTemp_f = utils.convertInputToTemp_f(thermistorReading_Vcounts);
    // currentTemp_f += 12;  // IMPORTANT! - Subtract 6 here to make temperature probe accurate at 155F.
    
    //
    // get valve setpoint based on current probe temp
    //
    valveSetpoint = utils.calcValveSetpoint(currentTemp_f, CurrentTempSetpoint_f);  // determines how big flame should be (analogWrite takes int)


    if (ValveSetpointOverride)
    {
      valveSetpoint = ValveSetpointOverride;  
    }
    if (debug)
    {
      printDebug();
    }
    analogWrite(ValvePin, valveSetpoint);  // set valve open amount
    
    delay(1000);
}
