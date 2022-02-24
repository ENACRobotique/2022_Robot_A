#ifndef CONFIG
#define CONFIG

#include <Arduino.h>

const int ENCODER_MOTOR1_A = 16;
const int ENCODER_MOTOR1_B = 17;
const int ENCODER_MOTOR2_A = 29;
const int ENCODER_MOTOR2_B = 30;
const int ENCODER_WHEEL1_A = 20;
const int ENCODER_WHEEL1_B = 21;
const int ENCODER_WHEEL2_A = 23;
const int ENCODER_WHEEL2_B = 22;
//const float PI = 3.14159;
const float ACCEL_MAX = 20; //m/s²
const float CONTROL_RATE = 25; //ms
const float ENCODER_RATE = 20000.f;
const int NB_INC_MOTOR = 3190;
const int NB_INC_WHEEL = 2707;
const float INC_TO_MM_MOTOR =0.001;
const float INC_TO_MM_WHEEL =8.14e-5;

const int MOT1_PWM = 6;//36;35
const int MOT1_DIR = 7;//33;34
const int MOT2_PWM = 9;//35;
const int MOT2_DIR = 8;//34;

#endif CONFIG