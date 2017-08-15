#ifndef ValveControl_h
#define ValveControl_h

class ValveControl
{
public:
    ValveControl(void);

    int calcSetpoint(float, int);

    ~ValveControl(void);
private:
    const int Low = 150;
    const int MedLow = 175;
    const int Med = 200;
    const int MedHigh = 225;
    const int High = 255;

};

#endif // valveControl_h
