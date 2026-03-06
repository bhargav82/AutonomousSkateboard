#include "controller.h"

static constexpr uint32_t closest_distance_cm = 100;
static constexpr uint32_t furthest_distance_cm = 500;
static constexpr uint32_t oldest_time_sec = 10;
void Controller::readSensor(SensorSlot* slots, uint8_t count) {
    SnapShot snaps[count];
    for (size_t slot = 0; slot < count; ++slot) {
        slots[slot].m.lock();
        snaps[slot].last_distance_cm = slots[slot].last_distance_cm;
        snaps[slot].last_recorded_time = slots[slot].last_recorded_time;
        snaps[slot].status = slots[slot].status;
        slots[slot].m.unlock();
    } // acquire each lock and read the latest data into local variables

    uint32_t min_distance_cm = UINT32_MAX;
    bool invalid = false;
    for (size_t snap = 0; snap < count && !invalid; ++snap) {
        if (snaps[snap].status == Status::Error) {
            invalid = true;
            break;
        }
        if (snaps[snap].last_recorded_time < oldest_time_sec) {
            continue;
        } else {
            if (snaps[snap].last_distance_cm < min_distance_cm) {
                min_distance_cm = snaps[snap].last_distance_cm;
            }
        }
    } // check for any invalid status, and update min distance if possible

    if (invalid) {
        command = Command::Stop;
    } else if  (min_distance_cm < closest_distance_cm) {
        comand = Command::SlowDown;
    } else if (min_distance_cm < furthest_distance_cm) {
        command = Command::Hold;
    } else {
        command = Command::SpeedUp;
    }
}