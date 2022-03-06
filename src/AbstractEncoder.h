#pragma once
class AbstractEncoder {
    public:
        AbstractEncoder();
        ~AbstractEncoder();
        virtual void init() {};
        //function to call periodically to update the encoder
        virtual void update() {};

    protected:
        volatile int counter;
};