#include "odom.h"
#include "Arduino.h"
#include "motor.h"
#include "../lib/metro.h"
#include "config.h"
#include "pid.h"

// float clamp(float inf, float sup, float x) {
// 	return min(sup, max(inf, x));
// }

float sign(float nb) {
	if(nb>0) {
		return 0;
	}
	else {
		return 1;
	}
}


PID pidSpeed=PID(1.0, 0.0, 0.0, -255.0, 255.0);
PID pidOmega=PID(1.0, 0.0, 0.0, -255.0, 255.0);

void MotorControl::set_cons(float speed, float omega) {
	timeTrapezoide = millis();
	//vitesseTrapezoide = Odometry::get_speed_motor();
	cons_speed = speed;
	cons_omega = omega;
}

void MotorControl::stop() {
	set_cons(0,0);
}
float MotorControl::get_cons_speed(){
	return cons_speed;
}

float MotorControl::get_cons_omega(){
	return cons_omega;
}

void MotorControl::init() {
	pinMode(MOT1_DIR, OUTPUT);
	pinMode(MOT1_PWM, OUTPUT);
	pinMode(MOT2_DIR, OUTPUT);
	pinMode(MOT2_PWM, OUTPUT);
	cons_omega = cons_speed = 0;
}

float MotorControl::trapeze(float cons){
	if (abs(ACCEL_MAX*(millis()-timeTrapezoide)*1e-3+vitesseTrapezoide) > abs(cons)){
		return cons;
	}
	else{
		return ((cons-vitesseTrapezoide) > 0) ? 1 : (((cons-vitesseTrapezoide) < 0) ? -1 : 0)*ACCEL_MAX*(millis()-timeTrapezoide)*1e-3+vitesseTrapezoide;
	}
}

void MotorControl::cmd_mot(float cmd_speed, float cmd_omega) { //cmd_speed in m/s and cmd_omega in rad/s
	if(cmd_speed == 0 && cmd_omega == 0) { //prevent "jerky" stop
		send_mot_signal(0, 0);
	}
	else {
		int cmd_mot1 = clamp(-255.f, 255.f, cmd_speed + cmd_omega);
		int cmd_mot2 = clamp(-255.f, 255.f, - (cmd_speed - cmd_omega));
		send_mot_signal(cmd_mot1, cmd_mot2);
	}
}
void MotorControl::send_mot_signal(int spdm1, int spdm2){ //speed motor in pwm signal (0-255)
		analogWrite(MOT1_PWM, abs(spdm1));
		digitalWrite(MOT1_DIR, sign(spdm1));
		analogWrite(MOT2_PWM, abs(spdm2));
		digitalWrite(MOT2_DIR, sign(spdm2));

}


void update(Odometry *odom) { //asservissement
	Serial2.println(get_cons_speed());
	float error_speed = trapeze(cons_speed) - (*odom).get_speed_motor();

	float cmd_speed = pidSpeed.update(error_speed);

	float error_omega = cons_omega - (*odom).get_omega_motor();

	float cmd_omega = pidOmega.update(error_omega);

	cmd_mot(cmd_speed, cmd_omega);

}
