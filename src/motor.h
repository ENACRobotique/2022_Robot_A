#ifndef MOTORCONTROL_H_
#define MOTORCONTROL_H_

//#define DEBUG_ASSERVISSEMENT

class MotorControl {
public:
	void update();
	void init();

	double get_cons_speed(){
		return cons_speed;
	}

	double get_cons_omega(){
		return cons_omega;
	}

	void cmd_mot(double cmd_speed, double cmd_omega);
	void send_mot_signal(int cmde1, int cmde2);
	void set_cons(double speed, double omega);
	void trapeze();
	void stop();
private:
	double goal_speed;
	double goal_omega;
	double cons_speed;
	double cons_omega;
};

extern MotorControl motor;

#endif /* MOTORCONTROL_H_ */
