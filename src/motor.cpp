#include "odom.h"
#include "Arduino.h"
#include "motor.h"
#include "metro.h"
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

	int timeTrap = 0;
	float vitesseTrap = 0;

	float Ki_speed = 0; //1
	float Kp_speed = 0; //8
	float Kd_speed = 0; //

	float Ki_omega = 0;//0.8
	float Kp_omega = 0;//2
	float Kd_omega = 0;//

	float error_integrale_speed=0;
	float error_integrale_omega=0;

	float delta_speed=0;
	float delta_omega=0;
	float prev_speed_error=0;
	float prev_omega_error=0;

	void set_cons(float speed, float omega) {
		timeTrap = millis();
		vitesseTrap = Odometry::get_speed_motor();
		cons_speed = speed;
		cons_omega = omega;
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
		if (abs(ACCEL_MAX*(millis()-timeTrap)*1e-3+vitesseTrap) > abs(cons)){
			return cons;
		}
		else{
			return ((cons-vitesseTrap) > 0) ? 1 : (((cons-vitesseTrap) < 0) ? -1 : 0)*ACCEL_MAX*(millis()-timeTrap)*1e-3+vitesseTrap;
		}
	}

	void test_motor(int spdm1, int spdm2){
		analogWrite(MOT1_PWM, abs(spdm1));
		digitalWrite(MOT1_DIR, sign(spdm1));
		analogWrite(MOT2_PWM, abs(spdm2));
		digitalWrite(MOT2_DIR, sign(spdm2));
	}


	void update() {

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

		int cmd_mot1 = clamp(-255.f, 255.f, cmd_speed + cmd_omega);
		int cmd_mot2 = clamp(-255.f, 255.f, cmd_speed - cmd_omega);

		analogWrite(MOT1_PWM, abs(cmd_mot1));
		digitalWrite(MOT1_DIR, sign(cmd_mot1));
		analogWrite(MOT2_PWM, abs(cmd_mot2));
		digitalWrite(MOT2_DIR, sign(cmd_mot2));
	}
}