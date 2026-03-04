#include "sensor.h"

Sensor::Sensor() {
    last_reading_is_valid = true;
    status = Status::CALIBRATING;
    raw_distance_cm = 0;
    filtered_distance = 0;
    last_recorded_time_ms = 0;
    consecutive_invalids = 0;
}

// brief: Initializes any one-time hardware setup updates status
// param: None
// returns: sucess/failure and updates status
bool Sensor::init() {
    // TODO
    return true;
}

// brief: Releases hardware resources and updates status
// param: None
// returns: None
void Sensor::shutdown() {
    // TODO

}

// brief: Attempts to read the sensor, if successful updates variables
// param: now_ms is the current time
// returns: true if sucessfull poll and update, false if otherwise
bool Sensor::poll(uint32_t now_ms) {
    // read sensor
    return true;
}

// brief: Checks if current time is stale 
// param: now_ms is the current time
// returns: true if time stince last recorded is stale, false otherwise
inline bool Sensor::isStale(uint32_t now_ms) {
    return now_ms - last_recorded_time_ms > stale_timeout_ms;
}   

// brief: Updates status based on staleness and count 
// param: now_ms is the current time
// returns: 
void Sensor::updateHealth(uint32_t now_ms) {
    if (isStale(now_ms)) {
        status = Status::STALE;
    }
}

// brief: Validates distance read in by sensor, should be within range
// param: distance_cm is the distance read from sensor
// returns: true if reading is consistent and valid, false otherwise
bool Sensor::validateReading(uint32_t distance_cm) const {
    return (min_range_cm < distance_cm && distance_cm < max_range_cm);
}

// brief: Applies filter to raw data
// param: previous_filtered is the filtered old distance
// param; new_raw is the new raw distance to be filtered
// returns: true if time stince last recorded is stale, false otherwise
uint32_t Sensor::applyFilter(uint32_t previous_filtered, uint32_t new_raw) {
    // TODO
    return 0;
}

// brief: Returns raw distance from sensor
// param: None
// returns: Raw distance in CM 
uint32_t Sensor::getRawDistanceCM() const {
    // TODO
    return 0;
}

// brief: Controller will use this filtered distance
// param: None
// returns: Return the filtered distance
uint32_t Sensor::getFilteredDistance() const {
    // TODO
    return 0;
}

// brief: Checks if the last reading was valid
// param: None
// returns: 
inline bool Sensor::lastReadingValid() const {
    return last_reading_is_valid;
}

// brief: Getter for status
// param: None
// returns: Status type
inline Status Sensor::getStatus() const {
    return status;
}

// brief: Getter for last_recorded_time 
// param: None
// returns: last_recorded_time_ms
inline uint32_t Sensor::getLastUpdateTimeMS() const {
    return last_recorded_time_ms;
}

// brief: Finds ID of sensor
// param: None
// returns: id of sensor, useful for logging/sensor management
inline uint8_t Sensor::getID() const {
    return sensor_id;
}

// brief: Clears fault state back to initial
// param: None
// returns: None
void Sensor::resetFaults() {
    status = Status::HEALTHY;
    last_reading_is_valid = true;
    consecutive_invalids = 0;
}