
#include "main.h"
//#include "test_encoder.h"
//#include "motor.h"
#include "InterruptEncoder.h"
#include <unity.h>
//#include <config.h>

//#define UNIT_TEST //Mandatory to avoid trying to include arduino.h

//TODO : test input/output of InterruptEncoder with mock encoder using ArduinoFake
//TODO : assert speed
//TODO : test free encoder
/*
void test_encoder_direction(InterruptEncoder const &encoder) { 
    //one should be left of the robot
    motor.init();

    TEST_ASSERT_EQUAL(0, encoder.get_value());

    motor.set_cons(0, 0);
    TEST_ASSERT_EQUAL(0, encoder.get_value());

    motor.send_mot_signal(1, 0);
    delay(100);
    int current_counter = encoder.get_value();
    TEST_ASSERT_TRUE(encoder.get_value() > 0);

    motor.send_mot_signal(0, 0);
    delay(100);
    int current_counter = encoder.get_value();
    TEST_ASSERT_EQUAL(current_counter, encoder.get_value());
    
    motor.send_mot_signal(-1, 0);
    delay(100);
    int current_counter = encoder.get_value();
    TEST_ASSERT_TRUE(encoder.get_value() < current_counter);
}

void test_encoder_direction_1() {
    test_encoder_direction(encoder_m1);
}
void test_encoder_direction_2() {
    test_encoder_direction(encoder_m2);
}
*/

/*
int main( int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_encoder_direction_1);
    RUN_TEST(test_encoder_direction_2);
    UNITY_END();

}
*/
/*
void test_encoder() {
    RUN_TEST(test_encoder_direction_1);
    RUN_TEST(test_encoder_direction_2);
}
*/
