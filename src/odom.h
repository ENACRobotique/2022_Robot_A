#ifndef ODOMETRY
#define ODOMETRY

#include <config.h>
#include <REncoder.h>
//#include <metro.h>

class Odometry{
    private :
        static REncoder encoder;
        
        //static IntervalTimer _timer; //only works on teensy
        //static Metro _timer;

        static int _inc_motor1;
        static int _inc_motor2;
        static int _inc_wheel1;
        static int _inc_wheel2;
    
        static int _pos_motor1;
        static int _pos_motor2;
        static int _pos_wheel1;
        static int _pos_wheel2;

        static float _speed_motor1;
        static float _speed_motor2;
        static float _speed_wheel1;
        static float _speed_wheel2;

        

    public :
        static void init();

        static float get_pos_motor();
        static float get_pos_wheel();
        static float get_speed_motor();
        static float get_omega_motor();
        static float get_speed_wheel();
        static float get_test1();
        static float get_test2();
        static void _update(); //function was private, moved to public
};

#endif