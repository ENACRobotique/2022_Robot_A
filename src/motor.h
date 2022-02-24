#ifndef MOTORCONTROL_H_
#define MOTORCONTROL_H_

//#define DEBUG_ASSERVISSEMENT

namespace MotorControl {
	void update();
	void init();

	float get_cons_speed();
	float get_cons_omega();

	void test_motor(int cmde1, int cmde2);
	void set_cons(float speed, float omega);
	float trapeze(float cons);
}


#endif /* MOTORCONTROL_H_ */