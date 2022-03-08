#pragma once
#include <Arduino.h>

template <typename T>
T clamp(T inf, T sup, T x) {
    return min(sup, max(inf, x));
}
