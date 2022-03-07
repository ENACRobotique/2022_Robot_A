#include "test_encoder.h"
#include "motor.h"
#include "InterruptEncoder.h"
#include <unity.h>
#include <config.h>

//#define UNIT_TEST //Mandatory to avoid trying to include arduino.h

//TODO : test input/output of InterruptEncoder with mock encoder using ArduinoFake
//TODO : assert speed
//TODO : test free encoder

void test_encoder_direction(volatile int* counter) { 
    //one should be left of the robot
    MotorControl::init();
    InterruptEncoder encoder = InterruptEncoder(counter);
    encoder.init();

    encoder.update();
    TEST_ASSERT_EQUAL(0, encoder.counter);

    MotorControl::set_cons(0, 0);
    encoder.update();
    encoder.update();
    TEST_ASSERT_EQUAL(0, encoder.counter);

    MotorControl::send_mot_signal(1, 0);
    delay(100);
    int current_counter = encoder.counter;
    encoder.update();
    TEST_ASSERT_TRUE(encoder.counter > 0);

    MotorControl::send_mot_signal(0, 0);
    delay(100);
    encoder.update();
    TEST_ASSERT_EQUAL(current_counter, encoder.counter);
    
    MotorControl::send_mot_signal(-1, 0);
    delay(100);
    encoder.update();
    TEST_ASSERT_TRUE(encoder.counter < current_counter);
}

void test_encoder_direction_1() {
    test_encoder_direction(&InterruptEncoder::MOTOR_1_counter);
}
void test_encoder_direction_2() {
    test_encoder_direction(&InterruptEncoder::MOTOR_2_counter);
}

void test_encoder() {
    
    UNITY_BEGIN();
    RUN_TEST(test_encoder_direction_1);
    RUN_TEST(test_encoder_direction_2);
    UNITY_END();
}
