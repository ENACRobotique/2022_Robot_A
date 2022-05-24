#ifndef ODOMETRY
#define ODOMETRY

#include <config.h>
#include "InterruptEncoder.h"
//#include <metro.h>

class Odometry{
public :
    Odometry(const InterruptEncoder& enc_1, const InterruptEncoder& enc_2, double inc_right_to_mm, double inc_left_to_mm, double diametre);
    void init();

    void set_pos (int x, int y, double theta){
        _x = x;
        _y = y;
        _theta =theta;
    }
    
    double get_speed_motor() {
        return _speed;
    }
    double get_omega_motor() {
        return _omega;
    }
    
    double get_x() {
        return _x;
    }
    double get_y() {
        return _y;
    }
    double get_theta() {
        return _theta;
    }

    void _update();
private:
    InterruptEncoder enc_1;
    InterruptEncoder enc_2;
    double inc_right_to_mm;
    double inc_left_to_mm;
    double diametre;
    double _x, _y, _theta;  // position
    double _speed, _omega; // speed

    uint32_t last_time;

};

extern Odometry odom;
extern Odometry odom_wheel;
extern InterruptEncoder encoder_m1;
extern InterruptEncoder encoder_m2;

#endif