// Define shared runtime state between threads
#pragma once
#include <stdint.h>
#include "top_level/enums.h"
#include <mutex>


// Need to prevent false sharing
// when two threads write to two objects that share a cache line
// when one makes a write, cache gets marked modified and invalidates any old version on other cores
// alignas(64) places each counter on its own 64-byte cache line boundary
struct alignas(64) SensorSlot {
    uint32_t last_distance_cm;
    uint32_t last_timestamp_ms;
    Status status;
    std::mutex m; // locked when writing by sensor & when reading by controller
};


