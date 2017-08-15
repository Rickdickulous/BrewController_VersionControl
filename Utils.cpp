#include "Utils.h"

extern bool debug;

Utils::Utils()
{

}


int Utils::getFlameInput(int* ticks)
{
    int retVal = 0;
    incomingByte = 0;
    if (debug)
    {
        Serial.print("ticks = ");
        Serial.println(*ticks);
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




    *ticks += 100;
}


Utils::~Utils()
{

}
