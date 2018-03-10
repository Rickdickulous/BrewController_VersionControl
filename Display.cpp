#include "Display.h"

double prevActualTemp = 0.0;
int prevTempSetpoint = 0;
int prevValveSetpoint = 0;
long prevPrimaryTimer = 0;

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
    tft.print("Mash Temp: ");
    
    tft.setCursor(5, 125);
    tft.print("Mash Time Min: ");

    // buttons
    for (int i=0; i < NumButtons; i++) {
       Button * button_ptr = static_cast<Button *>(buttons[i]);
       button_ptr->drawButton();
    }
    
    tft.setTextSize(2);  // reset text size for live updates
}


void Display::dispUpdate() {
    // *** Display Target Temp ***
    if (prevTempSetpoint != 0) {
        tft.setCursor(127, 25);
        tft.setTextColor(Bg);
        tft.print(prevTempSetpoint);
    }
    tft.setCursor(127, 25);
    tft.setTextColor(Tc);
    tft.print(currentTempSetpoint_f);
    prevTempSetpoint = currentTempSetpoint_f;

    if (prevPrimaryTimer != 0) {
        tft.setCursor(175, 125);
        tft.setTextColor(Bg);
        tft.print(prevPrimaryTimer);
    }
    tft.setCursor(175, 125);
    tft.setTextColor(Tc);
    tft.print(timer_sec);
    prevPrimaryTimer = timer_sec;
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
    tft_ptr->setCursor(170, 70);
    tft_ptr->setTextColor(RED);
    tft_ptr->setTextSize(3);
    tft_ptr->print("+");
}


void ControllerUp::checkIfAreaTouched(TS_Point& point) {
    if ( (coords.x_origin <= point.x) && (point.x <= (coords.x_origin + coords.width )) ) {
        if ( (coords.y_origin <= point.y) && (point.y <= (coords.y_origin + coords.height)) ) {
            currentTempSetpoint_f++;
        }
    }
}

void ControllerDown::drawButton() {
    tft_ptr->drawRect(coords.x_origin, coords.y_origin, coords.width, coords.height, BLACK);
    tft_ptr->setCursor(55, 70);
    tft_ptr->setTextColor(BLUE);
    tft_ptr->setTextSize(3);
    tft_ptr->print("-");
}

void ControllerDown::checkIfAreaTouched(TS_Point& point) {
    if ( ( coords.x_origin <= point.x ) && (point.x <= (coords.x_origin + coords.width)) ) {
        if ( ( coords.y_origin <= point.y) && (point.y <= (coords.y_origin + coords.height)) ) {
            currentTempSetpoint_f--;
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


