#include <odom.h>
#include <comm.h>
#include "InterruptEncoder.h"
#include "../lib/metro.h"

InterruptEncoder encoder_m1(ENCODER_MOTOR1_B, ENCODER_MOTOR1_A);
InterruptEncoder encoder_m2(ENCODER_MOTOR2_A, ENCODER_MOTOR2_B);
InterruptEncoder encoder_w1(ENCODER_WHEEL1_B, ENCODER_WHEEL1_A);
InterruptEncoder encoder_w2(ENCODER_WHEEL2_B, ENCODER_WHEEL2_A);

void Odometry::init() {
    encoder_m1.init();
    encoder_m2.init();
    encoder_w1.init();
    encoder_w2.init();
    if (digitalRead(COLOR) == HIGH){
        _x = 140.f; _y = 1140.f; _theta = 0;
    } else {
        _x = 3000.0f-140.f; _y = 1140.f; _theta = 3.1415;
    }
    
    _speed = 0; _omega = 0;
    last_time = 0;
}

void Odometry::_update() {
    uint32_t now = millis();
    double dt = (now - last_time) / 1000.0;
    last_time = now;

    Serial2.println("encoder value : ");
    Serial2.println(encoder_w1.get_value());
    Serial2.println(encoder_w2.get_value());
    //wheel motor encoder
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
