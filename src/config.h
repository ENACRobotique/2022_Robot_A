#ifndef CONFIG
#define CONFIG

//#ifdef UNIT_TEST
//    #include "ArduinoFake.h"
//#else
#include "Arduino.h"
//#endif

//#include <PinNames.h>

const int ENCODER_MOTOR1_A = PC6;
const int ENCODER_MOTOR1_B = PC8;
const int ENCODER_MOTOR2_A = PA11;
const int ENCODER_MOTOR2_B = PA12;
const int ENCODER_WHEEL1_A = PB5;
const int ENCODER_WHEEL1_B = PB4;
const int ENCODER_WHEEL2_A = PA7;
const int ENCODER_WHEEL2_B = PA12;

const double MOTOR_BASE = 180;
const float INC_TO_MM_MOTOR =0.309671275853851;
const float INC_TO_MM_WHEEL =8.14e-5;

const float ACCEL_MAX = 20; //m/s²
const float CONTROL_PERIOD = 20; //ms
const float ENCODER_PERIOD = 20.f;
const float COMM_RATE = 50; //ms
//const int NB_INC_MOTOR = 3190;
//const int NB_INC_WHEEL = 2707;


const int MOT1_PWM = PA9;//36;35
const int MOT1_DIR = PB2;//33;34
const int MOT2_PWM = PA8;//35;
const int MOT2_DIR = PB10;//34;


const int POELON_SERVO_PIN = PA0; //TODO: mettre le bon pin (PA0 servo1, PA1 servo2 ou PB0 servo3)
const int POELON_RETRACTED_ANGLE = 0; //TODO: mettre le bon angle
const int POELON_DEPLOYED_ANGLE = 90; //TODO: mettre le bon angle
const int POELON_PUSH_ANGLE = 0; //TODO: mettre le bon angle
const int POELON_ANGLE_TOL_MINUS = 0; //TODO: mettre le bon angle
const int POELON_ANGLE_TOL_PLUS = 0; //TODO: mettre le bon angle
const int POELON_READ_PIN = PB1;

//TODO: valeurs
const int POELON_READ_VIOLET_INF = 0;
const int POELON_READ_VIOLET_SUP = 0;
const int POELON_READ_JAUNE_INF = 0;
const int POELON_READ_JAUNE_SUP = 0;
const int POELON_READ_ROUGE_INF = 0;
const int POELON_READ_ROUGE_SUP = 0;


#endif //CONFIG