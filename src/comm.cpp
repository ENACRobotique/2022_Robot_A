#include <comm.h>

#include <Arduino.h>
#include <odom.h>
#include <motor.h>

namespace Comm {

    char buffer[70];
    int buf_index = 0;

    //Analyse des informations contenues dans les messages Serial2
    static void parse_data() {
        if(buffer[0] == 's') { //Stop
            MotorControl::set_cons(0,0);
            Serial2.print("stopping robot");
        }
        else if(buffer[0] == 'v') { //Vitesse
            int x,omega;
            int nb = sscanf(buffer, "v %d %d", &x, &omega);
            Serial2.print(nb);
            if(nb == 2) {
                Serial2.print(x);
                Serial2.print(" ");
                Serial2.println(omega);
                MotorControl::set_cons((float)x,(float)omega);
            }
        }
        else if(buffer[0] == 'a') //Actionneur (fonctionnement à deux états on/off seulement)
        {
            char actuator;
            int index, isOn;
            int params = sscanf(buffer, "a %c %d %d", &actuator, &index, &isOn);
            if (params == 3)
            {
                switch (actuator)
                {
                case 'p': //Pompes
                    //(desactivé pour le moment) ActuatorStorage::pompes[index].setState(isOn);
                    break;
                
                default:
                    Serial2.printf("Err: actionneur inconnu !");
                    break;
                }
            }
        }
    }

    //Récupération des derniers messages sur le buffer Serial2 et traitement
    void update(){
        int a = Serial2.available(); //nombre de charactères à lire sur le buffer Serial2
        if (a) {
            for (int i = 0; i < a; i ++){
                char c = Serial2.read();
                if (c=='\n') {
                    buffer[buf_index] = '\0';
                    parse_data();
                    buf_index = 0;
                }
                else if (c == '\r') {}
                else {
                    buffer[buf_index] = c;
                    buf_index ++;
                }
            }
        }

        #ifdef COMM_SPAM_ODOMETRY
            Serial2.print("m "); //Odométrie moteur
            Serial2.print(Odometry::get_speed_motor());
            Serial2.print(" ");
            Serial2.println(Odometry::get_omega_motor());
        #endif
    }

}