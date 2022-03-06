#include <odom.h>
#include "AbstractEncoder.h"
#include "InterruptEncoder.h"

REncoder Odometry::encoder = REncoder();

InterruptEncoder motor_encoder_1 = InterruptEncoder(&(InterruptEncoder::MOTOR_1_counter)); //TODO : To switch to abstractEncoder
InterruptEncoder motor_encoder_2 = InterruptEncoder(&(InterruptEncoder::MOTOR_2_counter)); //TODO : To switch to abstractEncoder


int Odometry::_inc_motor1 = 0;
int Odometry::_inc_motor2 = 0;
int Odometry::_inc_wheel1 = 0;
int Odometry::_inc_wheel2 = 0;
    
int Odometry::_pos_motor1 = 0;
int Odometry::_pos_motor2 = 0;
int Odometry::_pos_wheel1 = 0;
int Odometry::_pos_wheel2 = 0;

float Odometry::_speed_motor1 = 0;
float Odometry::_speed_motor2 = 0;
float Odometry::_speed_wheel1 = 0;
float Odometry::_speed_wheel2 = 0;

//IntervalTimer Odometry::_timer = IntervalTimer();

//Metro Odometry::_timer = Metro(ENCODER_RATE);


void Odometry::init() {
    //encoder.init();
    motor_encoder_1.init();
    motor_encoder_2.init();
    //_timer.begin(_update, ENCODER_RATE);
    //_timer.reset();
}

void Odometry::_update() {
    motor_encoder_1.update();
    motor_encoder_2.update();

/*
    int current_pos_motor1 = encoder.get_pos_M1();
    int current_pos_motor2 = encoder.get_pos_M2();
    int current_pos_wheel1 = encoder.get_pos_W1();
    int current_pos_wheel2 = encoder.get_pos_W2();

    _inc_motor1 = -(current_pos_motor1 - _pos_motor1);
    _inc_motor2 = -(current_pos_motor2 - _pos_motor2);
    _inc_wheel1 = -(current_pos_wheel1 - _pos_wheel1);
    _inc_wheel2 = -(current_pos_wheel2 - _pos_wheel2);

    Serial2.println(_inc_motor1);
    Serial2.println( _inc_motor2);
    _speed_motor1 = _inc_motor1*2*3.14159*1e6/(NB_INC_MOTOR*ENCODER_RATE);
    _speed_motor2 = _inc_motor2*2*3.14159*1e6/(NB_INC_MOTOR*ENCODER_RATE);
    _speed_wheel1 = _inc_wheel1*2*3.14159*1e6/(NB_INC_WHEEL*ENCODER_RATE);
    _speed_wheel2 = _inc_wheel2*2*3.14159*1e6/(NB_INC_WHEEL*ENCODER_RATE);

    _pos_motor1 = current_pos_motor1;
    _pos_motor2 = current_pos_motor2;
    _pos_wheel1 = current_pos_wheel1;
    _pos_wheel2 = current_pos_wheel2;

*/

}

float Odometry::get_test1() {
    return _speed_motor1;
}

float Odometry::get_test2() {
    return _speed_motor2;
}

float Odometry::get_pos_motor() {
    return (-_pos_motor1+_pos_motor2)/2;
}

float Odometry::get_pos_wheel() {
    return (_pos_wheel1+_pos_wheel2)/2;
}

float Odometry::get_speed_motor() {
    return (_speed_motor1+_speed_motor2)/2;
}

float Odometry::get_omega_motor() {
    return (_speed_motor1-_speed_motor2);
}

float Odometry::get_speed_wheel() {
    return (_speed_wheel1+_speed_wheel2)/2;
}