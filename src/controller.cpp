#include "controller.h"

void Controller::readSensor(SensorSlot* slots, uint8_t count) {
    uint32_t min_distance_cm = UINT32_MAX;
    for (size_t s = 0; s < count; ++s) {
        slots[s].m.lock();
        if ( *(slots + s).last_distance_cm < min_distance_cm) {
            min_distance_cm = slots[s].last_distance_cm;
        }  
        slots[s].m.unlock();
    }
    // acquire each lock and read the latest data, need to update variables

}