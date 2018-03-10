#include "Display.h"

double prevActualTemp = 0.0;
int prevTempSetpoint = 0;
int prevValveSetpoint = 0;
long prevPrimaryTimer = 0;

Display disp = Display();

void Display::init() {

    tft.begin();
        tft.fillScreen(Bg);
        
        // *** Capacitive Touch Setup ***
        if(!ctp.begin()) {
            Serial.println("Unable to initialize ctp!");
            tft.print("Cap Touch Init Failed!");
        }
    
    // constants
    disp.tft.setTextColor(Tc);
    disp.tft.setTextSize(2);
    
    disp.tft.setCursor(5, 25);
    disp.tft.print("Mash Temp: ");
    
    disp.tft.setCursor(5, 125);
    disp.tft.print("Mash Time Min: ");

    // buttons
    for (int i=0; i < disp.NumButtons; i++) {
       Button * button_ptr = static_cast<Button *>(buttons[i]);
       button_ptr->drawButton();
    }
    
    disp.tft.setTextSize(2);  // reset text size for live updates
}


void Display::dispUpdate() {
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

bool Display::touchControl(TS_Point& p) {
    for (int i=0; i < disp.NumButtons; i++) {
       Button * button_ptr = static_cast<Button *>(buttons[i]);
       button_ptr->checkIfAreaTouched(p);
    }
}

void ControllerUp::drawButton() {
    Serial.println("pm_TU_db");
    disp.tft.drawRect(coords.x_origin, coords.y_origin, coords.width, coords.height, BLACK);
    disp.tft.setCursor(170, 70);
    disp.tft.setTextColor(RED);
    disp.tft.setTextSize(3);
    disp.tft.print("+");
}


void ControllerUp::checkIfAreaTouched(TS_Point& point) {
    if ( (coords.x_origin <= point.x) && (point.x <= (coords.x_origin + coords.width )) ) {
        if ( (coords.y_origin <= point.y) && (point.y <= (coords.y_origin + coords.height)) ) {
            currentTempSetpoint_f++;
        }
    }
}

void ControllerDown::drawButton() {
    disp.tft.drawRect(coords.x_origin, coords.y_origin, coords.width, coords.height, BLACK);
    disp.tft.setCursor(55, 70);
    disp.tft.setTextColor(BLUE);
    disp.tft.setTextSize(3);
    disp.tft.print("-");
}

void ControllerDown::checkIfAreaTouched(TS_Point& point) {
    if ( ( coords.x_origin <= point.x ) && (point.x <= (coords.x_origin + coords.width)) ) {
        if ( ( coords.y_origin <= point.y) && (point.y <= (coords.y_origin + coords.height)) ) {
            currentTempSetpoint_f--;
        }
    }
}

void TimeUp::drawButton() {
    disp.tft.drawRect(coords.x_origin, coords.y_origin, coords.width, coords.height, BLACK);
    disp.tft.setCursor(170, 170);
    disp.tft.setTextColor(RED);
    disp.tft.print("+");
}

void TimeUp::checkIfAreaTouched(TS_Point& point) {
    if ( (coords.x_origin <= point.x ) && (point.x <= (coords.x_origin + coords.width)) ) {
        if ( coords.y_origin <= point.y && (point.y <= (coords.y_origin + coords.height)) ) {
            timer_sec++;
        }
    }
}

void TimeDown::drawButton() {
    disp.tft.drawRect(coords.x_origin, coords.y_origin, coords.width, coords.height, BLACK);
    disp.tft.setCursor(55, 170);
    disp.tft.setTextColor(BLUE);
    disp.tft.setTextSize(3);
    disp.tft.print("-");
}

void TimeDown::checkIfAreaTouched(TS_Point& point) {
    if ( (coords.x_origin <= point.x ) && (point.x <= (coords.x_origin + coords.width)) ) {
        if ( coords.y_origin <= point.y && (point.y <= (coords.y_origin + coords.height)) ) {
            timer_sec--;
        }
    }
}

void StartTimer::drawButton() {
    disp.tft.drawRect(coords.x_origin, coords.y_origin, coords.width, coords.height, BLACK);
    disp.tft.setCursor(90, 275);
    disp.tft.setTextSize(2);
    disp.tft.setTextColor(YELLOW);
    disp.tft.print("START TIMER");
}

void StartTimer::checkIfAreaTouched(TS_Point& point) {
    if ( (coords.x_origin <= point.x ) && (point.x <= (coords.x_origin + coords.width)) ) {
        if ( coords.y_origin <= point.y && (point.y <= (coords.y_origin + coords.height)) ) {
        }
    }
}


