#pragma once
class AbstractEncoder {
    public:
        virtual void init()=0;
        //function to call periodically to update the encoder
        virtual int get_value()=0;
};
