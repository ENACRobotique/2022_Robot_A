#pragma once
#include <Arduino.h>

template <typename T>
T clamp(T inf, T sup, T x) {
    return min(sup, max(inf, x));
}

constexpr bool testADCpin(PinName pin) {
  int i = 0;
  while(PinMap_ADC[i].pin != static_cast<PinName>(NC)) {
    if(PinMap_ADC[i].pin == pin) {
      return true;
    }
    i++;
  }
  return false;
}
