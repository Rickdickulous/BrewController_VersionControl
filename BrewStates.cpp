#include "BrewStates.h"
#include "Arduino.h"

double prevActualTemp = 0.0;
int prevTempSetpoint = 0;
int prevValveSetpoint = 0;
long prevPrimaryTimer = 0;

Display disp = Display();  // TODO: Move this variable into Display.cpp


void PreMash::dispInit() {
    //Serial.println("PreMash::dispInit() invoked");
    
    // since PreMash is the first state, we use it to initialize the display itself.
    disp.init();
    
    // now begin state init
    
    disp.tft.setTextColor(Tc);
    disp.tft.setTextSize(2);

    disp.tft.setCursor(5, 25);
    disp.tft.print("Mash Temp: ");
    
    for (int i=0; i < NumButtons; i++) {
       Button * button_ptr = static_cast<Button *>(buttons[i]);
       button_ptr->drawButton();
    }

    // ============= Mash Time =============
    
    disp.tft.setTextColor(Tc);
    disp.tft.setTextSize(2);
    disp.tft.setCursor(5, 125);
    disp.tft.print("Mash Time Min: ");

    // ============== BEGIN =============
    disp.tft.drawRect(30, 230, 160, 70, BLACK);
    disp.tft.setCursor(90, 275);
    disp.tft.setTextSize(2);
    disp.tft.setTextColor(YELLOW);
    disp.tft.print("BEGIN");

    disp.tft.setTextSize(2);  // reset text size for live updates
}


void PreMash::dispUpdate() {
    //Serial.println("PreMash::dispUpdate() invoked");

    // *** Display Target Temp ***
    if (prevTempSetpoint != 0) {
        disp.tft.setCursor(127, 25);
        disp.tft.setTextColor(Bg);
        disp.tft.print(prevTempSetpoint);
    }
    disp.tft.setCursor(127, 25);
    disp.tft.setTextColor(Tc);
    disp.tft.print(currentTempSetpoint_f);
    prevTempSetpoint = currentTempSetpoint_f;

    if (prevPrimaryTimer != 0) {
        disp.tft.setCursor(175, 125);
        disp.tft.setTextColor(Bg);
        disp.tft.print(prevPrimaryTimer);
    }
    disp.tft.setCursor(175, 125);
    disp.tft.setTextColor(Tc);
    disp.tft.print(timer_sec);
    prevPrimaryTimer = timer_sec;
}

bool PreMash::touchControl(TS_Point& p) {
    for (int i=0; i < NumButtons; i++) {
       Button * button_ptr = static_cast<Button *>(buttons[i]);
       button_ptr->checkIfAreaTouched(p);
    }
}


void Mash::dispInit() {
    Serial.println("Mash::dispInit() invoked");

    disp.tft.fillScreen(Bg);
    disp.tft.setTextColor(Tc);
    disp.tft.setTextSize(2);

    // *** Display Target Temp ***
    disp.tft.setCursor(0, 25);
    disp.tft.print("Target Temp: ");

    // *** Display Current Water Temp ***
    disp.tft.setCursor(0, 75);
    disp.tft.print("Actual Temp: ");

    // *** Display Valve Setpoint ***
    disp.tft.setCursor(0, 125);
    disp.tft.print("Valve Setpoint: ");

    disp.tft.drawRect(30, 175, 75, 100, BLACK);
    disp.tft.drawRect(140, 175, 75, 100, BLACK);

    disp.tft.setCursor(60, 210);
    disp.tft.setTextColor(BLUE);
    disp.tft.setTextSize(3);
    disp.tft.print("-");

    disp.tft.setCursor(170, 210);
    disp.tft.setTextColor(RED);
    disp.tft.print("+");

    disp.tft.setTextSize(2);  // reset text size for live updates  // TBD: Is this necessary?
}


void Mash::dispUpdate() {
    Serial.println("Mash::dispUpdate() invoked");

    // *** Display Target Temp ***
    if (prevTempSetpoint != 0) {
        disp.tft.setCursor(150, 25);
        disp.tft.setTextColor(Bg);
        disp.tft.print(prevTempSetpoint);
    }
    disp.tft.setCursor(150, 25);
    disp.tft.setTextColor(Tc);
    disp.tft.print(currentTempSetpoint_f);
    prevTempSetpoint = currentTempSetpoint_f;

    // *** Display Current Water Temp ***
    if (prevActualTemp != 0) {
        disp.tft.setCursor(150, 75);
        disp.tft.setTextColor(Bg);
        disp.tft.print(prevActualTemp);
    }
    disp.tft.setCursor(150, 75);
    disp.tft.setTextColor(Tc);
    disp.tft.print(utils.currentTemp_f);
    prevActualTemp = utils.currentTemp_f;

    // *** Display Valve Setpoint ***
    if (prevValveSetpoint != 0) {
        disp.tft.setCursor(185, 125);
        disp.tft.setTextColor(Bg);
        disp.tft.print(prevValveSetpoint);
    }

    disp.tft.setCursor(185, 125);
    disp.tft.setTextColor(Tc);
    disp.tft.println(utils_Ptr->valveSetpoint);
    prevValveSetpoint = utils_Ptr->valveSetpoint;
}


bool Mash::touchControl() {
  // return originalTouchControl(utils_Ptr);
}
