#include <comm.h>

#include <Arduino.h>
#include <odom.h>
#include <motor.h>
#include <poelon.h>

//recap des messages en entrée:
//v <int> <int>: commande de vitesse <linéaire * 1000> <omega * 1000>
//s : arrêt du robot
//b <char> <int> <int>: commande d'actionneurs binaires <code type act> <numéro de l'act> <on/off/etat>
//s d : déployer le pôelon
//s r : rétracter le pôelon
//s m : mesure une résistance
//s e : retourne l'état du pôelon (en place pour mesurer ou pas)
//s p : pousser un carré
//s a : autopousser un carré (mesure et pousser si ok) (nécessite d'avoir fourni la couleur cible au pôelon avant)
//s c <int> : paramétrer la couleur cible (0: vide, 1: ~470 Ohms (violet), 2: ~1,0 kOhm (jaune), 3: ~4,7 kOhms (rouge))

//recap des messages en sortie:
//m <string> : un message à display à l'utilisateur
//o <int> <int> : odométrie moteur <v lin> <v omega>
//s m <int> : résultat de mesure poelon
//s e <int> : état du pôelon
//s p : le carré a fini d'être poussé
//s a <int> : opération d'autopush finie: si (<couleur> < 10): carré non poussé car de couleur <couleur>, sinon, carré poussé car de couleur <couleur - 10>.
//s c <int> : confirmation de changement de couleur du mode auto-pôelon

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
            Serial2.print("speed : ");
            if(nb == 2) {
                Serial2.printf("m (v %d %d)\n", x, omega);
                MotorControl::set_cons(static_cast<float>(x)/1000.f,static_cast<float>(omega)/1000.f);
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
        else if (buffer[0] == 't') //test
        {
            int test_index;
            int params = sscanf(buffer, "t %d", &test_index);
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
        //#define or undef
        #undef COMM_SPAM_ODOMETRY
        #ifdef COMM_SPAM_ODOMETRY
            Serial2.print("o "); //Odométrie moteur
            Serial2.print(Odometry::get_speed_motor());
            Serial2.print(" ");
            Serial2.println(Odometry::get_omega_motor());
        #endif
    }

}