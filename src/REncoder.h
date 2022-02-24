#ifndef RENCODER
#define RENCODER

class REncoder{
    public:

    void init();
    int get_pos_M1();
    int get_pos_M2();
    int get_pos_W1();
    int get_pos_W2();
    
    private:
    
    static void updatePinMot1();
    static void updatePinMot2();
    static void updatePinWhl1();
    static void updatePinWhl2();

    static int statusMot1;
    static int statusMot2;
    static int statusWhl1;
    static int statusWhl2;

    static int positionMot1;
    static int positionMot2;
    static int positionWhl1;
    static int positionWhl2;
};
#endif