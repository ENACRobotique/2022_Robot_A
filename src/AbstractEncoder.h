#pragma once
class AbstractEncoder {
    public:
        AbstractEncoder();
        virtual ~AbstractEncoder();
        //function to call periodically to update the encoder
        virtual void update();

    protected:
        volatile int counter;
};