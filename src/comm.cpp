#include <comm.h>

#include <Arduino.h>
#include <odom.h>
#include <motor.h>
#include <poelon.h>


//recap des messages en entrée:
//v <int> <int>: commande de vitesse <linéaire * 1000> <omega * 1000>
//s : arrêt du robot
//b <char> <int> <int>: commande d'actionneurs binaires <code type act> <numéro de l'act> <on/off/etat>
//p d : déployer le pôelon
//p r : rétracter le pôelon
//p m : mesure une résistance
//p e : retourne l'état du pôelon (en place pour mesurer ou pas)
//p p : pousser un carré
//p a : autopousser un carré (mesure et pousser si ok) (nécessite d'avoir fourni la couleur cible au pôelon avant)
//p c <int> : paramétrer la couleur cible (0: vide, 1: ~470 Ohms (violet), 2: ~1,0 kOhm (jaune), 3: ~4,7 kOhms (rouge))

//recap des messages en sortie:
//m <string> : un message à display à l'utilisateur
//o <int> <int> : odométrie moteur <v lin> <v omega>
//p m <int> : résultat de mesure poelon
//p e <int> : état du pôelon
//p p : le carré a fini d'être poussé
//p a <int> : opération d'autopush finie: si (<couleur> < 10): carré non poussé car de couleur <couleur>, sinon, carré poussé car de couleur <couleur - 10>.
//p c <int> : confirmation de changement de couleur du mode auto-pôelon



namespace Comm {

    HardwareSerial &SerialCom = Serial3;

    char buffer[70];
    int buf_index = 0;

    //Analyse des informations contenues dans les messages SerialCom
    static void parse_data() {
        if(buffer[0] == 's') { //Stop
            motor.set_cons(0, 0);
            SerialCom.println("m Stopping robot.");
        }
        else if(buffer[0] == 'v') { //Vitesse
            int x,omega;
            int nb = sscanf(buffer, "v %d %d", &x, &omega);
            SerialCom.print("speed : ");
            if(nb == 2) {
                Serial2.printf("m (v %d %d)\n", x, omega);
                motor.set_cons(static_cast<float>(x)/1000.f,static_cast<float>(omega)/1000.f);
                SerialCom.printf("m (v %d %d)\n", x, omega);
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
                    SerialCom.printf("m Err: actionneur inconnu (%c) !\n", actuator);
                    break;
                }
            }
        }
        else if(buffer[0] == 'p'){ //Poêlon
            /*int mesure;
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
                    SerialCom.printf("p m %d\n", mesure);
                    break;
                case 'e': //état du poelon (renvoie déployé ou rétracté par message)
                    etat = Poelon::recupEtat();
                    SerialCom.printf("p e %d\n", etat);
                    break;
                case 'p': //pousser un carré
                    Poelon::pousserCarre();
                    SerialCom.printf("p p\n"); //le carré a été poussé
                    break;
                case 'a': //autopousser un carré
                    mesure = Poelon::autoPush();
                    SerialCom.printf("p a %d\n", mesure); //si 0, 1, 2, 3 -> carré non poussé | si 10, 11, 12, 13 -> carré poussé
                    break;
                case 'c': //changer la couleur du mode auto
                    nb = sscanf(buffer, "p c %d", &coul);
                    if (nb) {
                        Poelon::setCouleur(coul);
                        SerialCom.printf("p c %d\n", coul);
                    } else {
                        SerialCom.printf("m Err: couleur du poelon non changée.\n");
                    }
                    break;
                default:
                    SerialCom.printf("m Err: poelon n'a pas cette commande (%c).\n", buffer[2]);
                    break;
            }
            */
        } 
        else if (buffer[0] == 't') //test
        {
            int test_index;
            int params = sscanf(buffer, "t %d", &test_index);
        }
    }

    //Récupération des derniers messages sur le buffer SerialCom et traitement
    void update(){
        int a = SerialCom.available(); //nombre de charactères à lire sur le buffer SerialCom
        if (a) {
            for (int i = 0; i < a; i ++){
                char c = SerialCom.read();
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
            SerialCom.print("o "); //Odométrie moteur
            SerialCom.print(Odometry::get_speed_motor());
            SerialCom.print(" ");
            SerialCom.println(Odometry::get_omega_motor());
        #endif
    }

}