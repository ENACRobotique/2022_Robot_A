#pragma once

#include <Encoder.h>
#include <IntervalTimer.h>

class Odometry
{
private:
    static Encoder _enc_motor1;
    static Encoder _enc_motor2;
    static Encoder _enc_wheel1;
    static Encoder _enc_wheel2;

    static IntervalTimer _timer;

    static int _inc_motor1;
    static int _inc_motor2;
    static int _inc_wheel1;
    static int _inc_wheel2;

    static int _pos_motor1;
    static int _pos_motor2;
    static int _pos_wheel1;
    static int _pos_wheel2;

    static void _update();

public:
    static void init();
    
    static int pos_motor1();
    static int pos_motor2();
    static int pos_wheel1();
    static int pos_wheel2();
    
};