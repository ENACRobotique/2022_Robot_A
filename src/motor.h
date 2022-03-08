#ifndef MOTORCONTROL_H_
#define MOTORCONTROL_H_

//#define DEBUG_ASSERVISSEMENT

class MotorControl {
public:
	MotorControl();
	void update();
	void init();

	float get_cons_speed(){
		return cons_speed;
	}

	float get_cons_omega(){
		return cons_omega;
	}

	void send_mot_signal(int cmde1, int cmde2);
	void set_cons(float speed, float omega);
	float trapeze(float cons);
	void stop();
private:
	float cons_speed=0;
	float cons_omega=0;
	
	int timeTrapezoide = 0;
	float vitesseTrapezoide = 0;
};
#endif /* MOTORCONTROL_H_ */
