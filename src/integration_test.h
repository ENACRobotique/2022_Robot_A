#pragma once

namespace integration_test {
    #pragma region utils

    extern void launch_test(const char* test_name);
    extern void send_test_result(const char* test_name, const char* msg, bool success);

    #pragma endregion


    #pragma region test_encoder

    extern void test_encoder_stop_1();
    extern void test_encoder_forward_1();
    extern void test_encoder_backward_1();
    extern void test_encoder_stop_2();
    extern void test_encoder_forward_2();
    extern void test_encoder_backward_2();

    #pragma endregion
}