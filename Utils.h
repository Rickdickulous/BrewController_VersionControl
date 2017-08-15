#ifndef Utils_h
#define Utils_h

#include "Arduino.h"

class Utils
{
public:
    Utils();

    int getFlameInput(int*);

    ~Utils();
private:
    int incomingByte;

};


#endif // Utils_h
