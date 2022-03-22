
//Organization as this example :
//https://github.com/platformio/platformio-examples/tree/develop/cicd-setup/test

#define UNIT_TEST //Custom addition to make sure this flag is set to true

#include <unity.h>
#include "test_encoder.h"
#include "test_metro.h"
#include "test_comm.h"


 //Mandatory to avoid trying to include arduino.h

void setup() {
    UNITY_BEGIN();
    test_metro::test_metro();
    test_encoder::test_encoder();
    test_comm::test_comm();
    UNITY_END();

}

void loop() {

}