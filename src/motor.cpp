#include "odom.h"
#include "Arduino.h"
#include "motor.h"
#include "../lib/metro.h"
#include "config.h"

int clamp(int inf, int sup, float x) {
	return min(static_cast<float>(sup), max(static_cast<float>(inf), x));
}

float sign(float nb) {
	if(nb>0) {
		return 0;
	}
	else {
		return 1;
	}
}



namespace MotorControl {

	float cons_speed=0;
	float cons_omega=0;
	
	int timeTrapezoide = 0;
	float vitesseTrapezoide = 0;

	float Ki_speed = 1; //1
	float Kp_speed = 0; //8
	float Kd_speed = 0; //

	float Ki_omega = 1;//0.8
	float Kp_omega = 0;//2
	float Kd_omega = 0;//

	float error_integrale_speed=0;
	float error_integrale_omega=0;

	float delta_speed=0;
	float delta_omega=0;
	float prev_speed_error=0;
	float prev_omega_error=0;

	void set_cons(float speed, float omega) {
		timeTrapezoide = millis();
		vitesseTrapezoide = Odometry::get_speed_motor();
		cons_speed = speed;
		cons_omega = omega;
	}

	void stop() {
		set_cons(0,0);
	}
	float get_cons_speed(){
		return cons_speed;
	}

	float get_cons_omega(){
		return cons_omega;
	}

	void init() {
		pinMode(MOT1_DIR, OUTPUT);
		pinMode(MOT1_PWM, OUTPUT);
		pinMode(MOT2_DIR, OUTPUT);
		pinMode(MOT2_PWM, OUTPUT);
		cons_omega = cons_speed = 0;
		error_integrale_omega = error_integrale_speed = 0;
		prev_omega_error = prev_speed_error = 0;
	}

	float trapeze(float cons){
		if (abs(ACCEL_MAX*(millis()-timeTrapezoide)*1e-3+vitesseTrapezoide) > abs(cons)){
			return cons;
		}
		else{
			return ((cons-vitesseTrapezoide) > 0) ? 1 : (((cons-vitesseTrapezoide) < 0) ? -1 : 0)*ACCEL_MAX*(millis()-timeTrapezoide)*1e-3+vitesseTrapezoide;
		}
	}

	void cmd_mot(float cmd_speed, float cmd_omega) { //cmd_speed in m/s and cmd_omega in rad/s
		if(cmd_speed == 0 && cmd_omega == 0) { //prevent "jerky" stop
			send_mot_signal(0, 0);
		}
		else {
			int cmd_mot1 = clamp(-255.f, 255.f, cmd_speed + cmd_omega);
			int cmd_mot2 = clamp(-255.f, 255.f, - (cmd_speed - cmd_omega));
			send_mot_signal(cmd_mot1, cmd_mot2);
		}
	}
	void send_mot_signal(int spdm1, int spdm2){ //speed motor in pwm signal (0-255)
			analogWrite(MOT1_PWM, abs(spdm1));
			digitalWrite(MOT1_DIR, sign(spdm1));
			analogWrite(MOT2_PWM, abs(spdm2));
			digitalWrite(MOT2_DIR, sign(spdm2));

	}


	void update() { //asservissement
		Serial2.println(get_cons_speed());
		float error_speed = trapeze(cons_speed) - Odometry::get_speed_motor();
		error_integrale_speed += error_speed;
		delta_speed = error_speed - prev_speed_error;
		prev_speed_error = error_speed;

		float cmd_speed = Kp_speed * error_speed + Ki_speed * error_integrale_speed + Kd_speed * delta_speed;

		float error_omega = cons_omega - Odometry::get_omega_motor();
		error_integrale_omega += error_omega;
		delta_omega = error_omega - prev_omega_error;
		prev_omega_error = error_omega;
		
		float cmd_omega = Kp_omega * error_omega + Ki_omega * error_integrale_omega + Kd_omega * delta_omega;

		cmd_mot(cmd_speed, cmd_omega);

	}
}