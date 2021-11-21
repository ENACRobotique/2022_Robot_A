#include "odometry.h"
#include "config.h"

Encoder Odometry::_enc_motor1 = Encoder(ENCODER_MOTOR1_A, ENCODER_MOTOR1_B);
Encoder Odometry::_enc_motor2 = Encoder(ENCODER_MOTOR2_A, ENCODER_MOTOR2_B);
Encoder Odometry::_enc_wheel1 = Encoder(ENCODER_WHEEL1_A, ENCODER_WHEEL1_B);
Encoder Odometry::_enc_wheel2 = Encoder(ENCODER_WHEEL2_A, ENCODER_WHEEL2_B);

int Odometry::_inc_motor1 = 0;
int Odometry::_inc_motor2 = 0;
int Odometry::_inc_wheel1 = 0;
int Odometry::_inc_wheel2 = 0;
    
int Odometry::_pos_motor1 = 0;
int Odometry::_pos_motor2 = 0;
int Odometry::_pos_wheel1 = 0;
int Odometry::_pos_wheel2 = 0;

IntervalTimer Odometry::_timer = IntervalTimer();

void Odometry::init() {
    _timer.begin(_update, ENCODER_RATE);
}

void Odometry::_update() {
    int current_pos_motor1 = _enc_motor1.read();
    int current_pos_motor2 = _enc_motor2.read();
    int current_pos_wheel1 = _enc_wheel1.read();
    int current_pos_wheel2 = _enc_wheel2.read();

    _inc_motor1 = current_pos_motor1 - _pos_motor1;
    _inc_motor2 = current_pos_motor2 - _pos_motor2;
    _inc_wheel1 = current_pos_wheel1 - _pos_wheel1;
    _inc_wheel2 = current_pos_wheel2 - _pos_wheel2;

    _pos_motor1 = current_pos_motor1;
    _pos_motor2 = current_pos_motor2;
    _pos_wheel1 = current_pos_wheel1;
    _pos_wheel2 = current_pos_wheel2;
}


int Odometry::pos_motor1() {
    return _pos_motor1;
}

int Odometry::pos_motor2() {
    return _pos_motor2;
}

int Odometry::pos_wheel1() {
    return _pos_wheel1;
}

int Odometry::pos_wheel2() {
    return _pos_wheel2;
}