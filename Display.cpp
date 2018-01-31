#include "Display.h"


Button::Button() {
    Serial.println("Box created!");
}

void PreMash_TempUp::drawButton() {
    Serial.println("pm_TU_db");
    disp.tft.drawRect(coords.x_origin, coords.y_origin, coords.width, coords.height, BLACK);
    disp.tft.setCursor(170, 70);
    disp.tft.setTextColor(RED);
    disp.tft.print("+");
}


void PreMash_TempUp::checkIfAreaTouched(TS_Point& point) {
    
}


