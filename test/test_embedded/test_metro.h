#include <unity.h>
#include <../lib/metro.h>
#include "Arduino.h"

namespace test_metro {
    void test_check_metro() {
        Metro metro = Metro(100);
        TEST_ASSERT_FALSE(metro.check());
        delay(100);
        TEST_ASSERT_TRUE(metro.check());
        delay(20);
        TEST_ASSERT_FALSE(metro.check());
    }
    void test_metro() {
        RUN_TEST(test_check_metro);
    }

}