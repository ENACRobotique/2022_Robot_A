#pragma once
#include <Arduino.h>
#include "utils.h"

const float PROP_MAX_INTEGRAL=0.5;
class PID {
public:
    PID(float kp, float ki, float kd, float min, float max):
        kp(kp), ki(ki), kd(kd), min(min), max(max) {}
    float update(float error) {
        uint32_t now = millis();
        float dt = (now-prev_time)/1000.0;
        prev_time = now;
        float delta_error = (error - prev_error)/dt;
        prev_error = error;
        integral += error*dt;
        if (ki>0.00001){
            integral = clamp((min*PROP_MAX_INTEGRAL)/ki, (max*PROP_MAX_INTEGRAL)/ki, integral);
            // clamp intergral pour que ki*integral ne dépasse pas x% de max.
        }
        float output = kp * error + ki * integral + kd * delta_error;
        return clamp(min, max, output);
    }
    void reset();
    void set_kp(float kp) { this->kp = kp; }
    void set_ki(float ki){ this->ki = ki; }
    // void set_kd(float kd);
    // void set_min(float min);
    // void set_max(float max);
    // float get_kp();
    // float get_ki();
    // float get_kd();
    // float get_min();
    // float get_max();
private:
    float kp;
    float ki;
    float kd;
    float min;
    float max;
    float integral;
    float prev_error;
    uint32_t prev_time;
};
