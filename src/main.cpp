#include "include/sensor.h"
#include "include/shared_state.h"



static constexpr uint8_t numSlots = 4; // may change
int main() {
    SensorSlot slots[numSlots];

    Controller con;
    // loop every so often and call controller.readSensor
    while (true) {
        con.readSensor(slots);
    }
    return 0;
}