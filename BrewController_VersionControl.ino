// Dick Bilt Libraries
#include "Utils.h"
#include "Display.h"


// display libraries
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"


Utils utils = Utils();
Display disp = Display();


// variable declarations
float thermistorReading_Vcounts = 0.0;
unsigned long ticks_100ms = 0;  // print using lu
int flameSensorReading_counts = 1000;  // >900 means flame is on, so initialize to big number


// Pin Declarations
int const ValvePin = 6;
int const ThermistorPin = 0;
int const BuzzerPin = 8;
int const FlameSensorPin = 1;


// ** Override valve open setpoint **
int const ValveSetpointOverride = 0;  // Set to 0 to disable


// debug log
const bool debug = true;
void printDebug(void)
{
    if (debug)
    {
      STR(utils.currentTemp_f);
      STR(utils.CurrentTempSetpoint_f);
      STR(utils.valveSetpoint);
    }
}


void everythingTempControl()
{
    // valveSetpoint = utils.getFlameInput(ticks_100ms);

    //
    // get current probe temp degrees F
    //
    thermistorReading_Vcounts = analogRead(ThermistorPin);    // read the thermistor pin
    utils.convertInputToTemp_f(thermistorReading_Vcounts);
    // utils.currentTemp_f += 12;  // IMPORTANT! - Subtract 6 here to make temperature probe accurate at 155F.

    //
    // get valve setpoint based on current probe temp
    //
    utils.calcValveSetpoint();  // determines how big flame should be (analogWrite takes int)

    flameSensorReading_counts = analogRead(FlameSensorPin);
    utils.handleFlameSensor(flameSensorReading_counts);


    // boil state: display current valve setpoint and allow changing of it on screen. multiples of 5? maybe have 150 200 255 on screen?
    // TODO: filter temperature readings

    /* take in rows of brew params:
     *  (1) - Temp - have a BOIL input - temp to hit to start timer
     *  (2) - Time until next hop addition
     *  (3) - Display Output
     *
     *
     *  Have #define RICK and #define JIM to set min/max flame outputs
     */

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

    // delay(1000);
}

void setup()
{
    pinMode(ValvePin, OUTPUT);
    pinMode(BuzzerPin, OUTPUT);

    disp.init(utils);

    Serial.begin(9600);  // begin serial communication

    /*
    Serial.println("Hit a key to start");
    while( Serial.available() == 0 ) {}  // stays here until 1 or more bytes are pushed to the receive buffer
    Serial.flush();  // waits for data to finishing transmitting to the serial buffer before moving on
    */
}

void loop()
{
    everythingTempControl();
    disp.printOnScreen(utils);
    //disp.test();
    delay(1000);
}


