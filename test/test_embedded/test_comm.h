#include "unity.h"
#include "Arduino.h"
#include "comm.h"

// TEST only input, the output are tested on the raspberry side (as an input there)
//test only communication, not if the robot is working
/*
void test_stop() {
    motor.init();
    comm.parse_data('s');
    delay(100);
    TEST_ASSERT_EQUAL(0, motor.get_speed_m1());
    TEST_ASSERT_EQUAL(0, motor.get_speed_m2());
}

void test_pid() {
    motor.init();
    comm.parse_data('g 1 5 5 5');
    //todo : test pid
}

void test_speed() {
    motor.init();
    comm.parse_data('v 1 1');
    delay(100);
    //TEST ASSERT BETWEEN
}

void cmd_ax12() {

}

void cmd_electrovanne() {

}

void cmd_servo() {

}
*/
namespace test_comm {
    void test_comm() {
        
    };
}