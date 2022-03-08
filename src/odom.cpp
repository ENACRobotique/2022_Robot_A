#include <odom.h>
#include "InterruptEncoder.h"
#include "../lib/metro.h"

InterruptEncoder encoder_m1(ENCODER_MOTOR1_B, ENCODER_MOTOR1_A);
InterruptEncoder encoder_m2(ENCODER_MOTOR2_A, ENCODER_MOTOR2_B);

void Odometry::init() {
    encoder_m1.init();
    encoder_m2.init();
    _x = 0; _y = 0; _theta = 0;
    _speed = 0; _omega = 0;
    last_time = 0;
}

void Odometry::_update() {
    uint32_t now = millis();
    double dt = (now - last_time) / 1000.0;
    last_time = now;

    int inc_left = encoder_m1.get_value();
    int inc_right = encoder_m2.get_value();
    //Serial2.printf("%d %d\n", inc_left, inc_right);

    double dtheta = (inc_right - inc_left) * INC_TO_MM_MOTOR / MOTOR_BASE;
    _theta += dtheta;
    double lenght = ((inc_left + inc_right) / 2.0) * INC_TO_MM_MOTOR;
    _x += lenght * cos(_theta) ;
    _y += lenght * sin(_theta);

    _speed = lenght / dt;
    _omega = dtheta / dt;

    // Serial2.print(_speed);
    // Serial2.print(" ");
    // Serial2.println(_omega);

    // Serial2.print(_x);
    // Serial2.print(" ");
    // Serial2.print(_y);
    // Serial2.print(" ");
    // Serial2.println(_theta);

}
