#ifndef ODOMETRY
#define ODOMETRY

#include <config.h>
//#include <metro.h>

class Odometry{
public :
    void init();

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
    double _x, _y, _theta;  // position
    double _speed, _omega; // speed

    uint32_t last_time;

};

extern Odometry odom;

#endif