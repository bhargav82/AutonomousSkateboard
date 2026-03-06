#pragma once
#include <stdint.h>
enum class Position : uint8_t {
    FrontLeft,
    FrontRight,
    BackLeft,
    BackRight
};

enum class Status : uint8_t {
    HEALTHY,
    STALE,
    ERROR,
    CALIBRATING
};


enum class Command : uint8_t {
    SpeedUp,
    Hold,
    SlowDown,
    Stop
};