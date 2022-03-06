#include "AbstractEncoder.h"

class InterruptEncoder: public AbstractEncoder {
    public:
        InterruptEncoder(int* counter);
        int counter;
        void update();
        void init();

        //To use for initializing the encoder
        static volatile int MOTOR_1_counter;
        static volatile int MOTOR_2_counter;
        static volatile int WHEEL_1_counter;
        static volatile int WHEEL_2_counter;

        static void interrupt_handler_MOTOR_1(void);
        static void interrupt_handler_MOTOR_2(void);
        static void interrupt_handler_WHEEL_1(void);
        static void interrupt_handler_WHEEL_2(void);

        //TODO : reversed_interrupt_handler
        //Used for debug purposes, to check if A and B are correctly connected

    private:
        int* _inc;
};
//On file au constructeur l'index de l'interrupt handler correspondant à l'encoder
//L'interrupt handler a ces pins A et B déjà mis
//