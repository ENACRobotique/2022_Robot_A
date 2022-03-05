#include <comm.h>

#include <Arduino.h>
#include <odom.h>
#include <motor.h>
#include <poelon.h>

namespace Comm {

    char buffer[70];
    int buf_index = 0;

    //Analyse des informations contenues dans les messages Serial2
    static void parse_data() {
        if(buffer[0] == 's') { //Stop
            MotorControl::set_cons(0,0);
            Serial2.println("m Stopping robot.");
        }
        else if(buffer[0] == 'v') { //Vitesse
            int x,omega;
            int nb = sscanf(buffer, "v %d %d", &x, &omega);
            Serial2.print(nb);
            if(nb == 2) {
                Serial2.printf("m (v %d %d)\n", x, omega);
                MotorControl::set_cons((float)x,(float)omega);
            }
        }
        else if(buffer[0] == 'b') //Actionneurs binaires (fonctionnant à deux états (on/off) seulement)
        {
            char actuator;
            int index, isOn;
            int params = sscanf(buffer, "b %c %d %d", &actuator, &index, &isOn);
            if (params == 3)
            {
                switch (actuator)
                {
                case 'p': //Pompes
                    //(desactivé pour le moment) ActuatorStorage::pompes[index].setState(isOn);
                    break;
                
                default:
                    Serial2.printf("m Err: actionneur inconnu (%c) !\n", actuator);
                    break;
                }
            }
        }
        else if(buffer[0] == 's'){ //Poêlon (skillet en anglais)
            int mesure;
            int etat;
            int coul;
            int nb;
            switch (buffer[2]){
                case 'd': //deployer
                    Poelon::changerEtat(true);
                    break;
                case 'r': //retracter
                    Poelon::changerEtat(false);
                    break;
                case 'm': //mesurer
                    mesure = Poelon::lireResistance();
                    Serial2.printf("s m %d\n", mesure);
                    break;
                case 'e': //état du poelon (renvoie déployé ou rétracté par message)
                    etat = Poelon::recupEtat();
                    Serial2.printf("s e %d\n", etat);
                    break;
                case 'p': //pousser un carré
                    Poelon::pousserCarre();
                    Serial2.printf("s p\n"); //le carré a été poussé
                    break;
                case 'a': //autopousser un carré
                    mesure = Poelon::autoPush();
                    Serial2.printf("s a %d\n", mesure); //si 0, 1, 2, 3 -> carré non poussé | si 10, 11, 12, 13 -> carré poussé
                    break;
                case 'c': //changer la couleur du mode auto
                    nb = sscanf(buffer, "s c %d", &coul);
                    if (nb) {
                        Poelon::setCouleur(coul);
                        Serial2.printf("s c %d\n", coul);
                    } else {
                        Serial2.printf("m Err: couleur du poelon non changée.\n");
                    }
                    break;
                default:
                    Serial2.printf("m Err: poelon n'a pas cette commande (%c).\n", buffer[2]);
                    break;
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