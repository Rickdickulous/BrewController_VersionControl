// Dick Bilt Libraries
#include "Interface.h"
#include "Utils.h"
#include "Display.h"

Interface interface = Interface();


void setup()
{
    pinMode(VALVE_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);

    interface.init();
    
    Serial.begin(9600);  // begin serial communication
}

void loop()
{
    interface.brewsistantManager();
}


