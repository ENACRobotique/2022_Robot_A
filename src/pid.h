#pragma once
#include <Arduino.h>

float clamp(float inf, float sup, float x) {
	return min(sup, max(inf, x));
}

class PID {
public:
    PID(float kp, float ki, float kd, float min, float max):
        kp(kp), ki(ki), kd(kd), min(min), max(max) {}
    float update(float error) {
        uint32_t now = millis();
        int dt = now-prev_time;
        prev_time = now;
        float delta_error = (error - prev_error)/dt;
        prev_error = error;
        integral += error*dt;
        // clamp intergral pour que ki*integral ne dépasse pas x% de max.
        float output = kp * error + ki * integral + kd * delta_error;
        return clamp(min, max, output);
    }
    void reset();
    // void set_kp(float kp);
    // void set_ki(float ki);
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
