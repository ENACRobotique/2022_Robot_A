//ONLY TO USE FOR UNIT TEST
#pragma once

#include <Arduino.h>

#include "comm.h"
#include "config.h"
#include "motor.h"
#include "odom.h"
#include "../lib/metro.h"
#include "AX12A.h"
//#include "poelon.h"

extern Odometry odom;
extern MotorControl motor;
extern Comm radio;
extern DynamixelSerial AX12As;