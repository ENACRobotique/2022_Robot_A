
#include "main.h"
//#include "test_encoder.h"
//#include "motor.h"
#include "odom.h"
#include <unity.h>
//#include <config.h>

#define UNIT_TEST //Mandatory to avoid trying to include arduino.h

//TODO : test input/output of InterruptEncoder with mock encoder using ArduinoFake
//TODO : assert speed
//TODO : test free encoder



void test_encoder_stop_1() { //Use only when counter is at zero
    encoder_m1.get_value();
    motor.send_mot_signal(0, 0);
    delay(300);
    encoder_m1.get_value(); //Empty the get_value() (reset it to zero the time needed to decelerate)
    delay(100);
    TEST_ASSERT_EQUAL(0, encoder_m1.get_value());
}

void test_encoder_forward_1() {
    int current_counter = encoder_m1.get_value();
    motor.send_mot_signal(100, 0);
    delay(300);
    TEST_ASSERT_TRUE(encoder_m1.get_value() > current_counter);
}

void test_encoder_backward_1() {
    int current_counter = encoder_m1.get_value();
    motor.send_mot_signal(-100, 0);
    delay(300);
    TEST_ASSERT_TRUE(encoder_m1.get_value() < current_counter);
}
void test_encoder_stop_2() { //Use only when counter is at zero
    encoder_m2.get_value();
    motor.send_mot_signal(0, 0);
    delay(300);
    encoder_m2.get_value(); //Empty the get_value() (reset it to zero the time needed to decelerate)
    delay(100);
    TEST_ASSERT_EQUAL(0, encoder_m2.get_value());
}

void test_encoder_forward_2() {
    int current_counter = encoder_m2.get_value();
    motor.send_mot_signal(0, 100);
    delay(300);
    TEST_ASSERT_TRUE(encoder_m2.get_value() > current_counter);
}

void test_encoder_backward_2() {
    int current_counter = encoder_m2.get_value();
    motor.send_mot_signal(0, -100);
    delay(300);
    TEST_ASSERT_TRUE(encoder_m2.get_value() < current_counter);
}
void setup() {
    UNITY_BEGIN();
    motor.init();
    odom.init();
    RUN_TEST(test_encoder_stop_1);
    RUN_TEST(test_encoder_forward_1);
    RUN_TEST(test_encoder_stop_1);
    RUN_TEST(test_encoder_backward_1);
    RUN_TEST(test_encoder_stop_1);

    RUN_TEST(test_encoder_stop_2);
    RUN_TEST(test_encoder_forward_2);
    RUN_TEST(test_encoder_stop_2);
    RUN_TEST(test_encoder_backward_2);
    RUN_TEST(test_encoder_stop_2);
    //RUN_TEST(test_encoder_direction_2);
    UNITY_END();

}

void loop () {

}
/*
void test_encoder() {
    RUN_TEST(test_encoder_direction_1);
    RUN_TEST(test_encoder_direction_2);
}
*/
