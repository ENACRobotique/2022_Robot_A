#include "odom.h"
#include "Arduino.h"
#include "motor.h"
#include "../lib/metro.h"
#include "config.h"
#include "pid.h"
#include "utils.h"

double sign(double nb) {
	if(nb>0) {
		return 0;
	}
	else {
		return 1;
	}
}


PID pidSpeed=PID(0.5, 1, 0.0, -255.0, 255.0);
PID pidOmega=PID(40.0, 100.0, 0.0, -255.0, 255.0);

void MotorControl::set_cons(double speed, double omega) {
	last_cmd = millis();
	goal_speed = speed;
	goal_omega = omega;
}
void MotorControl::set_PID (char c, int kp, int ki){
	float kI = ki/10.0;
	float kP = kp/10.0;
	if (c=='s'){
		
		pidSpeed.set_kp(kP);
		pidSpeed.set_ki(kI);
	}
	else if (c=='o'){
		pidOmega.set_kp(kP);
		pidOmega.set_ki(kI);
	}
};
void MotorControl::stop() {
	goal_speed = 0;
	goal_omega = 0;
	cons_omega = 0;
	cons_speed = 0;
	pidOmega.reset();
	pidSpeed.reset();
}


void MotorControl::init() {
	pinMode(MOT1_DIR, OUTPUT);
	pinMode(MOT1_PWM, OUTPUT);
	pinMode(MOT2_DIR, OUTPUT);
	pinMode(MOT2_PWM, OUTPUT);
	cons_omega = cons_speed = 0;
	goal_omega = goal_speed = 0;
}

void MotorControl::trapeze(){
	double max_cons_speed = cons_speed + ACCEL_MAX*CONTROL_PERIOD/1000.0;
	double min_cons_speed = cons_speed - ACCEL_MAX*CONTROL_PERIOD/1000.0;

	cons_speed = clamp (min_cons_speed, max_cons_speed, goal_speed);

	double max_cons_omega = cons_omega + ACCEL_ANG_MAX*CONTROL_PERIOD/1000.0;
	double min_cons_omega = cons_omega - ACCEL_ANG_MAX*CONTROL_PERIOD/1000.0;

	cons_omega = clamp (min_cons_omega, max_cons_omega, goal_omega);

}

void MotorControl::cmd_mot(double cmd_speed, double cmd_omega) { //cmd_speed in m/s and cmd_omega in rad/s
	if(cons_speed == 0 && cons_omega == 0) { //prevent "jerky" stop
		send_mot_signal(0, 0);
	}
	else {
		int cmd_mot1 = clamp(-255.0, 255.0, cmd_speed - cmd_omega);
		int cmd_mot2 = clamp(-255.0, 255.0, - (cmd_speed + cmd_omega));
		send_mot_signal(cmd_mot1, -cmd_mot2);
	}
}
void MotorControl::send_mot_signal(int spdm1, int spdm2){ //speed motor in pwm signal (0-255)
		analogWrite(MOT1_PWM, abs(spdm1));
		digitalWrite(MOT1_DIR, sign(spdm1));
		analogWrite(MOT2_PWM, abs(spdm2));
		digitalWrite(MOT2_DIR, sign(spdm2));

}


void MotorControl::update() { //asservissement
	if (last_cmd + CMD_TIMEOUT > millis()){
		this->stop();
	}
	trapeze();
	double error_speed = cons_speed - odom.get_speed_motor();
	double cmd_speed = pidSpeed.update(error_speed);

	double error_omega = cons_omega - odom.get_omega_motor();
	double cmd_omega = pidOmega.update(error_omega);

	cmd_mot(cmd_speed, cmd_omega);

	// Serial2.print(cons_omega);
	// Serial2.print(" ");
	// Serial2.println(odom.get_omega_motor());
	// Serial2.print(" ");
	// Serial2.print(cmd_speed);
	// Serial2.print(" ");
	//Serial2.println(cmd_omega);
	//Serial2.print(" ");
// 	Serial2.print(cons_speed);
// 	Serial2.print(" ");
// 	Serial2.println(odom.get_speed_motor());
}


