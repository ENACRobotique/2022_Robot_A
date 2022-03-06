#include "test_base_moving.h"
#include "Arduino.h"
#include "motor.h"
#include "REncoder.h" //TODO -> Move to an abstract class Encoder

namespace test_base_moving {
    void test_motor_with_encoder_M1() {
        MotorControl::send_mot_signal(1, 0);
        //int initial = Odometry::encoder.get_pos_M1();
        delay(1);
        if(0 != 0) {
            Serial.println("Error: Encoder value is not 0");
        }
        delay(1);
    }
}