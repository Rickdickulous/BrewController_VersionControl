#include "Display.h"


void PreMash_TempUp::drawButton() {
    Serial.println("pm_TU_db");
    disp.tft.drawRect(coords.x_origin, coords.y_origin, coords.width, coords.height, BLACK);
    disp.tft.setCursor(170, 70);
    disp.tft.setTextColor(RED);
    disp.tft.print("+");
}


void PreMash_TempUp::checkIfAreaTouched(TS_Point& point) {
    if ( coords.x_origin <= point.x <= (coords.x_origin + coords.width) ) {
        if ( coords.y_origin <= point.y <= (coords.y_origin + coords.height) ) {
            utils_Ptr->currentTemp_f++;
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
    if ( coords.x_origin <= point.x <= (coords.x_origin + coords.width) ) {
        if ( coords.y_origin <= point.y <= (coords.y_origin + coords.height) ) {
            utils_Ptr->currentTemp_f--;
        }
    }
}

