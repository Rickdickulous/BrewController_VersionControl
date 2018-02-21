#include "Display.h"

// Display disp = Display();  // TODO: Move this variable from BrewStates.cpp to here

void PreMash_TempUp::drawButton() {
    Serial.println("pm_TU_db");
    disp.tft.drawRect(coords.x_origin, coords.y_origin, coords.width, coords.height, BLACK);
    disp.tft.setCursor(170, 70);
    disp.tft.setTextColor(RED);
    disp.tft.setTextSize(3);
    disp.tft.print("+");
}


void PreMash_TempUp::checkIfAreaTouched(TS_Point& point) {
    if ( (coords.x_origin <= point.x) && (point.x <= (coords.x_origin + coords.width )) ) {
        if ( (coords.y_origin <= point.y) && (point.y <= (coords.y_origin + coords.height)) ) {
            currentTempSetpoint_f++;
        }
    }
}

void PreMash_TempDown::drawButton() {
    disp.tft.drawRect(coords.x_origin, coords.y_origin, coords.width, coords.height, BLACK);
    disp.tft.setCursor(55, 70);
    disp.tft.setTextColor(BLUE);
    disp.tft.setTextSize(3);
    disp.tft.print("-");
}

void PreMash_TempDown::checkIfAreaTouched(TS_Point& point) {
    if ( ( coords.x_origin <= point.x ) && (point.x <= (coords.x_origin + coords.width)) ) {
        if ( ( coords.y_origin <= point.y) && (point.y <= (coords.y_origin + coords.height)) ) {
            currentTempSetpoint_f--;
        }
    }
}

void PreMash_TimeUp::drawButton() {
    disp.tft.drawRect(coords.x_origin, coords.y_origin, coords.width, coords.height, BLACK);
    disp.tft.setCursor(170, 170);
    disp.tft.setTextColor(RED);
    disp.tft.print("+");
}

void PreMash_TimeUp::checkIfAreaTouched(TS_Point& point) {
    if ( (coords.x_origin <= point.x ) && (point.x <= (coords.x_origin + coords.width)) ) {
        if ( coords.y_origin <= point.y && (point.y <= (coords.y_origin + coords.height)) ) {
            timer_sec++;
        }
    }
}

void PreMash_TimeDown::drawButton() {
    disp.tft.drawRect(coords.x_origin, coords.y_origin, coords.width, coords.height, BLACK);
    disp.tft.setCursor(55, 170);
    disp.tft.setTextColor(BLUE);
    disp.tft.setTextSize(3);
    disp.tft.print("-");
}

void PreMash_TimeDown::checkIfAreaTouched(TS_Point& point) {
    if ( (coords.x_origin <= point.x ) && (point.x <= (coords.x_origin + coords.width)) ) {
        if ( coords.y_origin <= point.y && (point.y <= (coords.y_origin + coords.height)) ) {
            timer_sec--;
        }
    }
}


