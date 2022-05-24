#include <odom.h>
#include <comm.h>
#include "InterruptEncoder.h"
#include "../lib/metro.h"

Odometry::Odometry(const InterruptEncoder& encoder_1, const InterruptEncoder& encoder_2, double inc_right_to_mm, double inc_left_to_mm, double diametre):
    enc_1(encoder_1),
    enc_2(encoder_2),
    inc_right_to_mm(inc_right_to_mm),
    inc_left_to_mm(inc_left_to_mm),
    diametre(diametre)
{
    
}
void Odometry::init() {
    enc_1.init();
    enc_2.init();
    if (digitalRead(COLOR) == HIGH){
        _x = 260.f; _y = 1140.f; _theta = 0;
    } else {
        _x = 3000.0f-260.f; _y = 1140.f; _theta = 3.1415;
    }
    
    _speed = 0; _omega = 0;
    last_time = 0;
}

void Odometry::_update() {
    uint32_t now = millis();
    double dt = (now - last_time) / 1000.0;
    last_time = now;

    static int inc_left_sum = 0;
    static int inc_right_sum = 0;


    //wheel motor encoder
    int inc_left;
    int inc_right;
    double dtheta;
    double lenght;


     // 1= utiliser les roues libres, 0= utiliser le moteur
       // wheel
        inc_left = enc_1.get_value();
        inc_right = enc_2.get_value();
        dtheta = (inc_right * inc_right_to_mm - inc_left * inc_left_to_mm) / diametre; // FIXME
        lenght = ((inc_left * inc_left_to_mm + inc_right * inc_right_to_mm) / 2.0); // FIXME
        if (0) //1 == calibrer les roues  - apparait les valeurs sur le diagnostic
        {
            inc_left_sum += inc_left;
            inc_right_sum += inc_right;
            Serial2.print("m ");
            if (inc_left_sum < 0) Serial2.print("-");
            Serial2.print(inc_left_sum);
            Serial2.print(" ");
            if (inc_right_sum < 0) Serial2.print("-");
            Serial2.println(inc_right_sum);
        }


    //Serial2.printf("%d %d\n", inc_left, inc_right);

     
    _theta += dtheta;
    _x += lenght * cos(_theta) ;
    _y += lenght * sin(_theta);

    _speed = lenght / dt;
    _omega = dtheta / dt;

    // Serial2.print(_speed);
    // Serial2.print(" ");
    // Serial2.println(_omega);

    // Serial2.print(_x);
    // Serial2.print(" ");
    // Serial2.print(_y);
    // Serial2.print(" ");
    // Serial2.println(_theta);

}
