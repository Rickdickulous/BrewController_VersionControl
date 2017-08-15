#include "TempController.h"

TempController::TempController(void) {}


float TempController::convertInputToTemp_F(float Vcounts)
{
    Rt = R1 / (1024/Vcounts - 1);
    float temp_C = (-26.65) * log(Rt) + 271.11;
    float temp_F = temp_C * 1.8 + 32;
    return temp_F;
}


float TempController::convertInputToTemp_C(float Vcounts)
{
    Rt = R1 / (1024/Vcounts - 1);
    float temp_C = (-26.65) * log(Rt) + 271.11;
    return temp_C;
}


float TempController::cToF(float temp_c)
{
    return temp_c * 1.8 + 32;
}


TempController::~TempController(void) {}
