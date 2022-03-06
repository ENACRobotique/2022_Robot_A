#include "AbstractEncoder.h"
#include "InterruptEncoder.h"
#include "config.h"

volatile int InterruptEncoder::MOTOR_1_counter = 0;
volatile int InterruptEncoder::MOTOR_2_counter = 0;
volatile int InterruptEncoder::WHEEL_1_counter = 0;
volatile int InterruptEncoder::WHEEL_2_counter = 0;


InterruptEncoder::InterruptEncoder(volatile int* counter) { //TODO : Pass by const reference
	_inc = counter;
	this->counter = 0;


}

InterruptEncoder::~InterruptEncoder() {
	//detachInterrupt //TODO
}

void InterruptEncoder::init() {
	//TODO : faire un switch case selon counter, si counter = MOTOR_1_counter, attachInterrupt(MOTOR_1_A_PIN, InterruptEncoder::interrupt_handler_MOTOR_1, CHANGE);
	pinMode(ENCODER_MOTOR1_A, INPUT_PULLUP);
    pinMode(ENCODER_MOTOR1_B, INPUT_PULLUP);
    pinMode(ENCODER_MOTOR2_A, INPUT_PULLUP);
    pinMode(ENCODER_MOTOR2_B, INPUT_PULLUP);
    pinMode(ENCODER_WHEEL1_A, INPUT_PULLUP);
    pinMode(ENCODER_WHEEL1_B, INPUT_PULLUP);
    pinMode(ENCODER_WHEEL2_A, INPUT_PULLUP);
    pinMode(ENCODER_WHEEL2_B, INPUT_PULLUP);
    attachInterrupt(ENCODER_MOTOR1_A, interrupt_handler_MOTOR_1,FALLING);
    //attachInterrupt(ENCODER_MOTOR1_B, interrupt_handler_MOTOR_1,CHANGE);
    attachInterrupt(ENCODER_MOTOR2_A, interrupt_handler_MOTOR_2,RISING);
    //attachInterrupt(ENCODER_MOTOR2_B, interrupt_handler_MOTOR_2,CHANGE);
    attachInterrupt(ENCODER_WHEEL1_A, interrupt_handler_WHEEL_1,FALLING);
    //attachInterrupt(ENCODER_WHEEL1_B, interrupt_handler_WHEEL_1,CHANGE);
    attachInterrupt(ENCODER_WHEEL2_A, interrupt_handler_WHEEL_2,RISING);
    //attachInterrupt(ENCODER_WHEEL2_B, interrupt_handler_WHEEL_2,CHANGE);
}

void InterruptEncoder::update() {
	this->counter += *_inc;
	*_inc = 0;
}

void InterruptEncoder::interrupt_handler_MOTOR_1() {
   	if(digitalRead(ENCODER_MOTOR1_B)) {
		MOTOR_1_counter++;
	}
	else {
		MOTOR_1_counter--;
	}
}

void InterruptEncoder::interrupt_handler_MOTOR_2() {
   	if(digitalRead(ENCODER_MOTOR2_B)) {
		MOTOR_2_counter++;
	}
	else {
		MOTOR_2_counter--;
	}
}

void InterruptEncoder::interrupt_handler_WHEEL_1() {
   	if(digitalRead(ENCODER_WHEEL1_B)) {
		WHEEL_1_counter++;
	}
	else {
		WHEEL_1_counter--;
	}
}

void InterruptEncoder::interrupt_handler_WHEEL_2() {
   	if(digitalRead(ENCODER_WHEEL2_B)) {
		WHEEL_2_counter++;
	}
	else {
		WHEEL_2_counter--;
	}
}



