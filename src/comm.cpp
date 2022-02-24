#include <comm.h>

#include <Arduino.h>
#include <odom.h>

namespace Comm {

    char buffer[70];
    char buf_index = 0;

    //Analyse des informations contenues dans les messages Serial
    static void parse_data() {
        if(buffer[0] == 's') { //Stop
            MotorControl::set_cons(0,0);
        }
        else if(buffer[0] == 'v') { //Vitesse
            float x,omega;
            int nb = sscanf(buffer, "v %f %f", &x, &omega);
            if(nb == 2) {   
                MotorControl::set_cons(x,omega);
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
                    ActuatorStorage::pompes[index].setState(isOn);
                    break;
                
                default:
                    Serial.printf("Err: actionneur inconnu !");
                    break;
                }
            }
        }
    }

    //Récupération des derniers messages sur le buffer Serial et traitement
    void update(){
        int a = Serial.available(); //nombre de charactères à lire sur le buffer serial
        if (a) {
            for (int i = 0; i < a; i ++){
                char c = Serial.read();
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
            Serial.print("m "); //Odométrie moteur
            Serial.print(Odometry::get_speed_motor());
            Serial.print(" ");
            Serial.println(Odometry::get_omega_motor());
        #endif
    }

}