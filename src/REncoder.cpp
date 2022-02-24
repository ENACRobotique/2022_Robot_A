#include "config.h"
#include "REncoder.h"
#include "Arduino.h"

int REncoder::statusMot1 = 0;
int REncoder::statusMot2 = 0;
int REncoder::statusWhl1 = 0;
int REncoder::statusWhl2 = 0;
int REncoder::positionMot1 = 0;
int REncoder::positionMot2 = 0;
int REncoder::positionWhl1 = 0;
int REncoder::positionWhl2 = 0;


void REncoder::init(){
    pinMode(ENCODER_MOTOR1_A, INPUT_PULLUP);
    pinMode(ENCODER_MOTOR1_B, INPUT_PULLUP);
    pinMode(ENCODER_MOTOR2_A, INPUT_PULLUP);
    pinMode(ENCODER_MOTOR2_B, INPUT_PULLUP);
    pinMode(ENCODER_WHEEL1_A, INPUT_PULLUP);
    pinMode(ENCODER_WHEEL1_B, INPUT_PULLUP);
    pinMode(ENCODER_WHEEL2_A, INPUT_PULLUP);
    pinMode(ENCODER_WHEEL2_B, INPUT_PULLUP);
    attachInterrupt(ENCODER_MOTOR1_A, updatePinMot1,CHANGE);
    attachInterrupt(ENCODER_MOTOR1_B, updatePinMot1,CHANGE);
    attachInterrupt(ENCODER_MOTOR2_A, updatePinMot2,CHANGE);
    attachInterrupt(ENCODER_MOTOR2_B, updatePinMot2,CHANGE);
    attachInterrupt(ENCODER_WHEEL1_A, updatePinWhl1,CHANGE);
    attachInterrupt(ENCODER_WHEEL1_B, updatePinWhl1,CHANGE);
    attachInterrupt(ENCODER_WHEEL2_A, updatePinWhl2,CHANGE);
    attachInterrupt(ENCODER_WHEEL2_B, updatePinWhl2,CHANGE);
}

void REncoder::updatePinMot1(){
		uint8_t s = statusMot1 & 3;
		if (digitalRead(ENCODER_MOTOR1_A)) s |= 4;
		if (digitalRead(ENCODER_MOTOR1_B)) s |= 8;
        switch (s) {
        case 0: case 5: case 10: case 15:
            break;
        case 1: case 7: case 8: case 14:
            positionMot1++; break;
        case 2: case 4: case 11: case 13:
            positionMot1--; break;
        case 3: case 12:
            positionMot1 += 2; break;
        default:
            positionMot1 -= 2; break;
    }
    statusMot1 = (s >> 2);
}

void REncoder::updatePinMot2(){
		uint8_t s = statusMot2 & 3;
		if (digitalRead(ENCODER_MOTOR2_A)) s |= 4;
		if (digitalRead(ENCODER_MOTOR2_B)) s |= 8;
        switch (s) {
        case 0: case 5: case 10: case 15:
            break;
        case 1: case 7: case 8: case 14:
            positionMot2++; break;
        case 2: case 4: case 11: case 13:
            positionMot2--; break;
        /*case 3: case 12:
            positionWhl1 += 2; break;
        default:
            positionWhl1 -= 2; break;*/
        default:
            break;
    }
    statusMot2 = (s >> 2);
}

void REncoder::updatePinWhl1(){
		uint8_t s = statusWhl1 & 3;
		if (digitalRead(ENCODER_WHEEL1_A)) s |= 4;
		if (digitalRead(ENCODER_WHEEL1_B)) s |= 8;
        switch (s) {
        case 0: case 5: case 10: case 15:
            break;
        case 1: case 7: case 8: case 14:
            positionWhl1++; break;
        case 2: case 4: case 11: case 13:
            positionWhl1--; break;
        /*case 3: case 12:
            positionWhl1 += 2; break;
        default:
            positionWhl1 -= 2; break;*/
        default:
            break;
    }
    statusWhl1 = (s >> 2);
}

void REncoder::updatePinWhl2(){
		uint8_t s = statusWhl2 & 3;
		if (digitalRead(ENCODER_WHEEL2_A)) s |= 4;
		if (digitalRead(ENCODER_WHEEL2_B)) s |= 8;
        switch (s) {
        case 0: case 5: case 10: case 15:
            break;
        case 1: case 7: case 8: case 14:
            positionWhl2++; break;
        case 2: case 4: case 11: case 13:
            positionWhl2--; break;
        /*case 3: case 12:
            positionWhl1 += 2; break;
        default:
            positionWhl1 -= 2; break;*/
        default:
            break;
    }
    statusWhl2 = (s >> 2);
}

int REncoder::get_pos_M1(){
    return positionMot1;
}
int REncoder::get_pos_M2(){
    return -positionMot2;
}
int REncoder::get_pos_W1(){
    return positionWhl1;
}
int REncoder::get_pos_W2(){
    return positionWhl2;
}