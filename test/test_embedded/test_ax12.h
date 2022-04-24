#include "unity.h"
#include "Arduino.h"
#include "AX12A.h"
#include "main.h"

namespace test_ax12 {
    void test_not_moving(char ID) {

    }

    void sequence_arm_1() { //arm in front
        const unsigned char ID = '6';
        TEST_MESSAGE(AX12As.moving(ID));
        TEST_ASSERT_TRUE(AX12As.moving(ID));
    }
    void test_ax12() {
        RUN_TEST(sequence_arm_1);
    };
}