#include "AbstractEncoder.h"
#include "InterruptEncoder.h"
#include "config.h"

InterruptEncoder::InterruptEncoder(int* counter) {
    int* _inc = counter;
}

void InterruptEncoder::init() {
	pinMode(ENCODER_MOTOR1_A, INPUT_PULLUP);
    pinMode(ENCODER_MOTOR1_B, INPUT_PULLUP);
    pinMode(ENCODER_MOTOR2_A, INPUT_PULLUP);
    pinMode(ENCODER_MOTOR2_B, INPUT_PULLUP);
    pinMode(ENCODER_WHEEL1_A, INPUT_PULLUP);
    pinMode(ENCODER_WHEEL1_B, INPUT_PULLUP);
    pinMode(ENCODER_WHEEL2_A, INPUT_PULLUP);
    pinMode(ENCODER_WHEEL2_B, INPUT_PULLUP);
    attachInterrupt(ENCODER_MOTOR1_A, interrupt_handler_MOTOR_1,CHANGE);
    attachInterrupt(ENCODER_MOTOR1_B, interrupt_handler_MOTOR_1,CHANGE);
    attachInterrupt(ENCODER_MOTOR2_A, interrupt_handler_MOTOR_2,CHANGE);
    attachInterrupt(ENCODER_MOTOR2_B, interrupt_handler_MOTOR_2,CHANGE);
    attachInterrupt(ENCODER_WHEEL1_A, interrupt_handler_WHEEL_1,CHANGE);
    attachInterrupt(ENCODER_WHEEL1_B, interrupt_handler_WHEEL_1,CHANGE);
    attachInterrupt(ENCODER_WHEEL2_A, interrupt_handler_WHEEL_2,CHANGE);
    attachInterrupt(ENCODER_WHEEL2_B, interrupt_handler_WHEEL_2,CHANGE);
}

void update() {
	this->counter += &_inc;
}

void InterruptEncoder::interrupt_handler_MOTOR_1(void) {
   	if(digitalRead(ENCODER_MOTOR1_B)) {
		InterruptEncoder::MOTOR_1_counter++;
	}
	else {
		MOTOR_1_counter--;
	}
}

void InterruptEncoder::interrupt_handler_MOTOR_1(void) {
   	if(digitalRead(ENCODER_MOTOR2_B)) {
		InterruptEncoder::MOTOR_2_counter++;
	}
	else {
		MOTOR_2_counter--;
	}
}

void InterruptEncoder::interrupt_handler_MOTOR_1(void) {
   	if(digitalRead(ENCODER_WHEEL1_B)) {
		InterruptEncoder::WHEEL_1_counter++;
	}
	else {
		WHEEL_1_counter--;
	}
}

void InterruptEncoder::interrupt_handler_MOTOR_1(void) {
   	if(digitalRead(ENCODER_WHEEL2_B)) {
		InterruptEncoder::WHEEL_2_counter++;
	}
	else {
		WHEEL_2_counter--;
	}
}



