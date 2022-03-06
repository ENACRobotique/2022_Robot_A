#pragma once

class HardwareEncoder{
    public:

    void init();
    int get_pos_encoder();
    
    private:
    
    static void update_encoder();
};

