// Defines controller interface
// Inputs: latest sensor readings
// Outputs: decision/command

#pragma once
#include "enums.h"

struct Controller{
    Command command;
    void readSensor(SensorSlots* s, uint8_t size);

};