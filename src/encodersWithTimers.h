#pragma once
//#include <hal.h>
//#include <ch.h>

 
class timerEncoders{
    public:
        void init();
        void update();
        long getValueEnc1(){return valueEnc1;}
        long getValueEnc2(){return valueEnc2;}
        
    private:
        volatile long valueEnc1;
        volatile long valueEnc2;

        //HardwareTimer timEnc1;
        //HardwareTimer timEnc2;

};