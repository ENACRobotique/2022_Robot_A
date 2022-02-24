#ifndef CONFIG
#define CONFIG

#include <Arduino.h>
#include <PinNames.h>

const int ENCODER_MOTOR1_A = PC6;
const int ENCODER_MOTOR1_B = PC8;
const int ENCODER_MOTOR2_A = PA11;
const int ENCODER_MOTOR2_B = PA12;
const int ENCODER_WHEEL1_A = PB5;
const int ENCODER_WHEEL1_B = PB4;
const int ENCODER_WHEEL2_A = PA7;
const int ENCODER_WHEEL2_B = PA12;
//const float PI = 3.14159;
const float ACCEL_MAX = 20; //m/s²
const float CONTROL_RATE = 25; //ms
const float ENCODER_RATE = 20000.f;
const float ENCODER_RATE_MILLIS = 20.f;
const int NB_INC_MOTOR = 3190;
const int NB_INC_WHEEL = 2707;
const float INC_TO_MM_MOTOR =0.001;
const float INC_TO_MM_WHEEL =8.14e-5;

const int MOT1_PWM = PA9;//36;35
const int MOT1_DIR = PB2;//33;34
const int MOT2_PWM = PA8;//35;
const int MOT2_DIR = PB10;//34;

#endif //CONFIG