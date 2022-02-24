//Code copied from Metro Library
//Copyright (c) 2013 thomasfredericks
//Under MIT License

#ifndef METRO
#define METRO

#include <Arduino.h>

class Metro {
    public:
        Metro() {
            this->interval_millis = 1000;
        }
        Metro(unsigned long millis_) {
            this->interval_millis = millis_;
        }
        void interval(unsigned long millis_){
            this->interval_millis = millis_;
        }
        bool check(){
            unsigned long now = millis();
            if (interval_millis == 0){
                previous_millis = now;
                return true;
            }
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