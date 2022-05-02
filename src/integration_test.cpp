#include "integration_test.h"
#include "main.h"
#include "odom.h"

namespace integration_test {
    #pragma region utils

    void launch_test(const char* test_name) {
        //TODO : faire un "dictionnaire" qui associe un string de test avec une fonction ici
    }
    //TODO : a vérifier en dessous uniquement autogénéré
    void send_test_result(const char* test_name, const char* msg, bool success) {
        Serial2.print("Test ");
        Serial2.print(test_name);
        Serial2.print(" : ");
        if (success) {
            Serial2.println("OK");
        } else {
            Serial2.println("FAIL");
        }
    }
    #pragma endregion


    #pragma region test_encoder

    void test_encoder_stop_1() { //Use only when counter is at zero
    encoder_m1.get_value();
    motor.send_mot_signal(0, 0);
    delay(300);
    encoder_m1.get_value(); //Empty the get_value() (reset it to zero the time needed to decelerate)
    delay(100);
    send_test_result("test_encoder_stop_1", "", (encoder_m1.get_value() == 0));
    }

    void test_encoder_forward_1() {
        int current_counter = encoder_m1.get_value();
        motor.send_mot_signal(100, 0);
        delay(300);
        send_test_result("test_encoder_forward_1", "", (encoder_m1.get_value() > current_counter));
    }

    void test_encoder_backward_1() {
        int current_counter = encoder_m1.get_value();
        motor.send_mot_signal(-100, 0);
        delay(300);
        send_test_result("test_encoder_backward_1", "", (encoder_m1.get_value() < current_counter));
    }
    void test_encoder_stop_2() { //Use only when counter is at zero
        encoder_m2.get_value();
        motor.send_mot_signal(0, 0);
        delay(300);
        encoder_m2.get_value(); //Empty the get_value() (reset it to zero the time needed to decelerate)
        delay(100);
        send_test_result("test_encoder_stop_2", "", (encoder_m2.get_value() == 0));
    }

    void test_encoder_forward_2() {
        int current_counter = encoder_m2.get_value();
        motor.send_mot_signal(0, 100);
        delay(300);
        send_test_result("test_encoder_forward_2", "", (encoder_m2.get_value() > current_counter));
    }

    void test_encoder_backward_2() {
        int current_counter = encoder_m2.get_value();
        motor.send_mot_signal(0, -100);
        delay(300);
        send_test_result("test_encoder_backward_2", "", (encoder_m2.get_value() < current_counter));
    }

    #pragma endregion
}