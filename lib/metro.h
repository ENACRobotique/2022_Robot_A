//Code copied from Metro Library
//Copyright (c) 2013 thomasfredericks
//Under MIT License

#ifndef METRO
#define METRO

#include <Arduino.h>

class Metro {
    public:
        Metro(unsigned long millis_): interval_millis(millis_) {}
        
        void interval(unsigned long millis_){
            this->interval_millis = millis_;
        }
        bool check(){
            unsigned long now = millis();
            if (interval_millis == 0){
                previous_millis = now;
                return true;
            }
            //Serial2.print(now);
            //Serial2.print(" ");
            //Serial2.print(previous_millis);
            //Serial2.print(" ");
            //Serial2.println(interval_millis);
            if ((now-previous_millis) >= interval_millis){
                
                #ifdef NOCATCHUP
                previous_millis = now;
                #else
                previous_millis += interval_millis;
                #endif
                return true;
            }
            return false;
        }
        void reset(){
            this->previous_millis = millis();
        }
    private:
        unsigned long previous_millis, interval_millis;
};

#endif