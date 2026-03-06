// Defines the sensor abstraction
#pragma once
#include <stdint.h>
#include "top_level/enums.h"

class Sensor {
private:
    uint32_t filtered_distance;
    uint32_t raw_distance_cm;
    uint32_t last_recorded_time_ms;
    uint32_t consecutive_invalids;
    static constexpr uint32_t stale_timeout_ms = 1000;
    static constexpr uint32_t max_consecutive_invalids = 10;

    uint8_t sensor_id;
    uint8_t mount_angle;        // degree to front axis
    uint8_t min_range_cm;
    uint8_t max_range_cm;
   
    Position position;          // fl, fr, bl, br
    Status status;
    bool last_reading_is_valid;
   

public:

    // brief: Initializes identifiy, mounting, config, bounds, and state
    // param: None
    // returns: None 
    Sensor();

    // brief: Initializes any one-time hardware setup updates status
    // param: None
    // returns: sucess/failure and updates status
    bool init();
    
    // brief: Releases hardware resources and updates status
    // param: None
    // returns: None
    void shutdown();

    // brief: Attempts to read the sensor, if successful updates variables
    // param: now_ms is the current time
    // returns: true if sucessfull poll and update, false if otherwise
    bool poll(uint32_t now_ms);

    // brief: Checks if current time is stale 
    // param: now_ms is the current time
    // returns: true if time stince last recorded is stale, false otherwise
    inline bool isStale(uint32_t now_ms);

    // brief: Updates status based on staleness and count 
    // param: now_ms is the current time
    // returns: 
    void updateHealth(uint32_t now_ms);

    // brief: Validates distance read in by sensor, should be within range
    // param: distance_cm is the distance read from sensor
    // returns: true if reading is consistent and valid, false otherwise
    bool validateReading(uint32_t distance_cm) const;

    // brief: Applies filter to raw data
    // param: previous_filtered is the filtered old distance
    // param; new_raw is the new raw distance to be filtered
    // returns: true if time stince last recorded is stale, false otherwise
    uint32_t applyFilter(uint32_t previous_filtered, uint32_t new_raw);

    // brief: Returns raw distance from sensor
    // param: None
    // returns: Raw distance in CM 
    uint32_t getRawDistanceCM() const;

    // brief: Controller will use this filtered distance
    // param: None
    // returns: Return the filtered distance
    uint32_t getFilteredDistance() const;

    // brief: Checks if the last reading was valid
    // param: None
    // returns: 
    inline bool lastReadingValid() const;

    // brief: Getter for status
    // param: None
    // returns: Status type
    inline Status getStatus() const;

    // brief: Getter for last_recorded_time 
    // param: None
    // returns: last_recorded_time_ms
    inline uint32_t getLastUpdateTimeMS() const;

    // brief: Finds ID of sensor
    // param: None
    // returns: id of sensor, useful for logging/sensor management
    inline uint8_t getID() const;

    // brief: Clears fault state back to initial
    // param: None
    // returns: None
    void resetFaults();

};
