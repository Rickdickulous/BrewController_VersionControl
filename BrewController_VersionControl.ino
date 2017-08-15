#include "TempController.h"  // TODO: Update name to TempSensor
# include "ValveControl.h"
#include "Utils.h"

int ThermistorPin = 0;
int valvePin = 10;
float Vcounts = 0.0;
float currentTemp = 0.0;
int valveSetpoint;
int currentTempSetpoint_F = 90;
int ticks_100ms = 0;

TempController tempController = TempController();  // temperature control module
ValveControl valveController = ValveControl();
Utils utils = Utils();


const bool debug = false;

void setup()
{

    pinMode(valvePin, OUTPUT);

    // enable all pins 0 - 12 for output mode
    for (int i; i < 18; i++)
    {
         pinMode(i, OUTPUT);
    }

    Serial.begin(9600);  // begin serial communication

    /*
    Serial.println("Hit a key to start");
    while( Serial.available() == 0 ) {}  // stays here until 1 or more bytes are pushed to the receive buffer
    Serial.flush();  // waits for data to finishing transmitting to the serial buffer before moving on
    */
}

void loop()
{
    // valveSetpoint = utils.getFlameInput(&ticks_100ms);


    Vcounts = analogRead(ThermistorPin);    // read the thermistor pin

    //
    // get current probe temp in degrees F
    //

    currentTemp = tempController.convertInputToTemp_F(Vcounts);
    if (debug)
    {
      Serial.print("currentTemp (F) = ");
      Serial.println(currentTemp);
    }

    
    for (int i; i < 18; i++)
    {
         analogWrite(i, 250);
         Serial.print("Output pin = ");
         Serial.println(i);
         delay(1500);
    }

    /*
    // Loop over valve control output settings
    for (int i = 100; i < 255; i++)
    {
      analogWrite(valvePin, i);
      if (debug)
      {
        Serial.print("Valve = ");
        Serial.println(i);
      }
      delay(300);  
    }
    */

    //
    // get valve setpoint based on current probe temp
    //

    /*
    valveSetpoint = valveController.calcSetpoint(currentTemp, currentTempSetpoint_F);  // determines how big flame should be (analogWrite takes int)

    if (debug)
    {
      Serial.print("valveSetpoint = ");
      Serial.println(valveSetpoint);
    }
   // set valve open amount
    analogWrite(valvePin, valveSetpoint);
    */

}
