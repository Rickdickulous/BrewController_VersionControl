#include "Display.h"

double prevActualTemp = 0.0;
int prevTempSetpoint = 0;
int prevValveSetpoint = 0;
long prevPrimaryTimer = 0;
double prevCurrentTemp = 0.0;
int currentTempToDisplay = 0;
bool resetScreen = false;

void Display::init() {

    tft.begin();
    tft.fillScreen(Bg);
    
    // *** Capacitive Touch Setup ***
    if(!ctp.begin()) {
        Serial.println("Unable to initialize ctp!");
        tft.print("Cap Touch Init Failed!");
    }
    
    // constants
    tft.setTextColor(Tc);
    tft.setTextSize(2);
    
    tft.setCursor(5, 25);
    tft.print("Current Temp: ");

    if (controlMode == CLOSED_LOOP) {
        tft.setCursor(5, 60);
        tft.print("Target Temp: ");
    }
    else if (controlMode == OPEN_LOOP) {
        // setup display for valve control
        tft.setCursor(5, 60);
        tft.print("Valve setpoint: ");
    }
    
    // tft.setCursor(5, 125);
    // tft.print("Mash Time Min: ");

    // buttons
    for (int i=0; i < NumButtons; i++) {
       Button * button_ptr = static_cast<Button *>(buttons[i]);
       button_ptr->drawButton();
    }
    
    tft.setTextSize(2);  // reset text size for live updates
}


void Display::dispUpdate() {
    if (resetScreen) {
      init();
      resetScreen = false;
      prevValveSetpoint = valveSetpoint;
    }
    
    if (controlMode == CLOSED_LOOP) {
        // *** Display Target Temp ***
        if (prevTempSetpoint != 0) {
            tft.setCursor(150, 60);
            tft.setTextColor(Bg);
            tft.print(prevTempSetpoint);
        }
        tft.setCursor(150, 60);
        tft.setTextColor(Tc);
        tft.print(currentTempSetpoint_f);
        prevTempSetpoint = currentTempSetpoint_f;
    }
    else if (controlMode == OPEN_LOOP) {
        // *** Display Valve Setpoint ***
        Serial.print("pv = ");
        Serial.println(prevValveSetpoint);
        Serial.print("cv = ");
        Serial.println(valveSetpoint);
       
        tft.setCursor(190, 60);
        tft.setTextColor(Bg);
        tft.print(prevValveSetpoint);

        tft.setCursor(190, 60);
        tft.setTextColor(Tc);
        tft.print(valveSetpoint);
        prevValveSetpoint = valveSetpoint;
    }
    
    // *** Display Current Temp ***
    Serial.print("ct = ");
    Serial.println(currentTemp_f);
    currentTempToDisplay = (int)(currentTemp_f + 0.5);

    tft.setCursor(170, 25);
    tft.setTextColor(Bg);
    tft.print(prevCurrentTemp);
    
    tft.setCursor(170, 25);
    tft.setTextColor(Tc);
    tft.print(currentTempToDisplay);
    prevCurrentTemp = currentTempToDisplay;
    
    /*
    if (prevPrimaryTimer != 0) {
        tft.setCursor(175, 125);
        tft.setTextColor(Bg);
        tft.print(prevPrimaryTimer);
    }
    tft.setCursor(175, 125);
    tft.setTextColor(Tc);
    tft.print(timer_sec);
    prevPrimaryTimer = timer_sec;
    */
}

bool Display::touchControl(TS_Point& p) {
    for (int i=0; i < NumButtons; i++) {
       Button * button_ptr = static_cast<Button *>(buttons[i]);
       button_ptr->checkIfAreaTouched(p);
    }
}

void ControllerUp::drawButton() {
    Serial.println("pm_TU_db");
    tft_ptr->drawRect(coords.x_origin, coords.y_origin, coords.width, coords.height, BLACK);
    tft_ptr->setCursor(170, 88);
    tft_ptr->setTextColor(RED);
    tft_ptr->setTextSize(3);
    tft_ptr->print("+");
}


void ControllerUp::checkIfAreaTouched(TS_Point& point) {
    if ( (coords.x_origin <= point.x) && (point.x <= (coords.x_origin + coords.width )) ) {
        if ( (coords.y_origin <= point.y) && (point.y <= (coords.y_origin + coords.height)) ) {
            if (controlMode == CLOSED_LOOP) {
                currentTempSetpoint_f++;
            }
            else if (controlMode == OPEN_LOOP) {
                prevValveSetpoint = valveSetpoint;
                valveSetpoint++;
            }
        }
    }
}

void ControllerDown::drawButton() {
    tft_ptr->drawRect(coords.x_origin, coords.y_origin, coords.width, coords.height, BLACK);
    tft_ptr->setCursor(60, 88);
    tft_ptr->setTextColor(BLUE);
    tft_ptr->setTextSize(3);
    tft_ptr->print("-");
}

void ControllerDown::checkIfAreaTouched(TS_Point& point) {
    if ( ( coords.x_origin <= point.x ) && (point.x <= (coords.x_origin + coords.width)) ) {
        if ( ( coords.y_origin <= point.y) && (point.y <= (coords.y_origin + coords.height)) ) {
            if (controlMode == CLOSED_LOOP) {
                currentTempSetpoint_f--;
            }
            else if (controlMode == OPEN_LOOP) {
                prevValveSetpoint = valveSetpoint;
                valveSetpoint--;
            }
        }
    }
}

void TimeUp::drawButton() {
    tft_ptr->drawRect(coords.x_origin, coords.y_origin, coords.width, coords.height, BLACK);
    tft_ptr->setCursor(170, 170);
    tft_ptr->setTextColor(RED);
    tft_ptr->print("+");
}

void TimeUp::checkIfAreaTouched(TS_Point& point) {
    if ( (coords.x_origin <= point.x ) && (point.x <= (coords.x_origin + coords.width)) ) {
        if ( coords.y_origin <= point.y && (point.y <= (coords.y_origin + coords.height)) ) {
            timer_sec++;
        }
    }
}

void TimeDown::drawButton() {
    tft_ptr->drawRect(coords.x_origin, coords.y_origin, coords.width, coords.height, BLACK);
    tft_ptr->setCursor(55, 170);
    tft_ptr->setTextColor(BLUE);
    tft_ptr->setTextSize(3);
    tft_ptr->print("-");
}

void TimeDown::checkIfAreaTouched(TS_Point& point) {
    if ( (coords.x_origin <= point.x ) && (point.x <= (coords.x_origin + coords.width)) ) {
        if ( coords.y_origin <= point.y && (point.y <= (coords.y_origin + coords.height)) ) {
            timer_sec--;
        }
    }
}

void StartTimer::drawButton() {
    tft_ptr->drawRect(coords.x_origin, coords.y_origin, coords.width, coords.height, BLACK);
    tft_ptr->setCursor(90, 275);
    tft_ptr->setTextSize(2);
    tft_ptr->setTextColor(YELLOW);
    tft_ptr->print("START TIMER");
}

void StartTimer::checkIfAreaTouched(TS_Point& point) {
    if ( (coords.x_origin <= point.x ) && (point.x <= (coords.x_origin + coords.width)) ) {
        if ( coords.y_origin <= point.y && (point.y <= (coords.y_origin + coords.height)) ) {
        }
    }
}

void ChangeMode::drawButton() {
    tft_ptr->drawRect(coords.x_origin, coords.y_origin, coords.width, coords.height, BLACK);
    tft_ptr->setCursor(47, 265);
    tft_ptr->setTextColor(PURPLE);
    tft_ptr->setTextSize(2);
    tft_ptr->print("Change Mode");
}

void ChangeMode::checkIfAreaTouched(TS_Point& point) {
    if ( (coords.x_origin <= point.x ) && (point.x <= (coords.x_origin + coords.width)) ) {
        if ( coords.y_origin <= point.y && (point.y <= (coords.y_origin + coords.height)) ) {
            resetScreen = true;
            controlMode = (controlMode + 1) % 2;
            Serial.println(controlMode);
        }
    }
}
