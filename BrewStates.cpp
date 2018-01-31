#include "BrewStates.h"
#include "Arduino.h"

double prevActualTemp = 0.0;
int prevTempSetpoint = 0;
int prevValveSetpoint = 0;
long prevPrimaryTimer = 0;

Display disp = Display();

/*
bool originalTouchControl(Utils * const utils_Ptr) {
  // TO BE DELETED
  

    //p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    //p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());


    // is button press within +/- button y range?
    if ( 165 <= p.y <= 265 ) {
        // yes! Based on x value, is it an up or down press?
        if ( (30 <= p.x) && ( p.x <= 90) ) {
            utils_Ptr->currentTempSetpoint_f--;
        }
        else if ( (130 <= p.x) && (p.x <= 210) ) {
            utils_Ptr->currentTempSetpoint_f++;
        }
        return true;
    }
    else {
        return false;
    }
}
*/


void PreMash::dispInit() {
    //Serial.println("PreMash::dispInit() invoked");
    
    // since PreMash is the first state, we use it to initialize the display itself.
    disp.init();
    
    // now begin state init
    
    disp.tft.setTextColor(Tc);
    disp.tft.setTextSize(2);

    disp.tft.setCursor(5, 25);
    disp.tft.print("Mash Temp: ");

    // drawRect(x, y, width, height)
    // minus
    disp.tft.drawRect(30, 50, 80, 60, BLACK);
    disp.tft.setCursor(55, 70);
    disp.tft.setTextColor(BLUE);
    disp.tft.setTextSize(3);
    disp.tft.print("-");

    // plus
    disp.tft.drawRect(140, 50, 80, 60, BLACK);
    disp.tft.setCursor(170, 70);
    disp.tft.setTextColor(RED);
    disp.tft.print("+");

    // ============= Mash Time =============
    
    disp.tft.setCursor(5, 125);
    disp.tft.setTextColor(Tc);
    disp.tft.setTextSize(2);
    disp.tft.print("Mash Time: ");

    // minus
    disp.tft.drawRect(30, 150, 80, 60, BLACK);
    disp.tft.setCursor(55, 170);
    disp.tft.setTextColor(BLUE);
    disp.tft.setTextSize(3);
    disp.tft.print("-");

    // plus
    disp.tft.drawRect(140, 150, 80, 60, BLACK);
    disp.tft.setCursor(170, 170);
    disp.tft.setTextColor(RED);
    disp.tft.print("+");

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
        disp.tft.setCursor(150, 25);
        disp.tft.setTextColor(Bg);
        disp.tft.print(prevTempSetpoint);
    }
    disp.tft.setCursor(150, 25);
    disp.tft.setTextColor(Tc);
    disp.tft.print(utils_Ptr->currentTempSetpoint_f);
    prevTempSetpoint = utils_Ptr->currentTempSetpoint_f;

    if (prevPrimaryTimer != 0) {
        disp.tft.setCursor(150, 75);
        disp.tft.setTextColor(Bg);
        disp.tft.print(prevPrimaryTimer);
    }
    disp.tft.setCursor(150, 125);
    disp.tft.setTextColor(Tc);
    disp.tft.print(utils_Ptr->primaryTimer.getRemainingTime());
    prevPrimaryTimer = utils_Ptr->primaryTimer.getRemainingTime();
}


bool PreMash::touchControl(TS_Point&) {
    // loop through array of buttons and call checkIfAreaTouched();
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
    disp.tft.print(utils_Ptr->currentTempSetpoint_f);
    prevTempSetpoint = utils_Ptr->currentTempSetpoint_f;

    // *** Display Current Water Temp ***
    if (prevActualTemp != 0) {
        disp.tft.setCursor(150, 75);
        disp.tft.setTextColor(Bg);
        disp.tft.print(prevActualTemp);
    }
    disp.tft.setCursor(150, 75);
    disp.tft.setTextColor(Tc);
    disp.tft.print(utils_Ptr->currentTemp_f);
    prevActualTemp = utils_Ptr->currentTemp_f;

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
