#include "comm.h"

#include <Arduino.h>
#include "odom.h"
#include "motor.h"
//#include "poelon.h"
#include "AX12A.h"
#include "elecvannes.h"


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



  
    //Analyse des informations contenues dans les messages SerialCom
void Comm::parse_data() {
        if(buffer[0] == 's') { //Stop
            motor.set_cons(0, 0);
            SerialCom.println("m Stopping robot.");
        }
        else if (buffer[0] == 'g'){
            int kp, ki;
            char c;
            int nbRec = sscanf (buffer, "g %c %d %d", &c, &kp, &ki );
            if (nbRec == 3){
                motor.set_PID(c, kp, ki);
                SerialCom.println("m Gains changed.");
            }
            else {
                SerialCom.println("m Error: wrong number of arguments.");
            }
        }
        else if(buffer[0] == 'v') { //Vitesse
            int x,omega;
            int nb = sscanf(buffer, "v %d %d", &x, &omega);
            if(nb == 2) {
                motor.set_cons(static_cast<float>(x),static_cast<float>(omega)/10.f);
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
        // else if(buffer[0] == 'p'){ //Poêlon
        //     int mesure;
        //     int etat;
        //     int coul;
        //     int nb;
        //     switch (buffer[2]){
        //         case 'd': //deployer
        //             poel.changerEtat(true);
        //             break;
        //         case 'r': //retracter
        //             poel.changerEtat(false);
        //             break;
        //         case 'm': //mesurer
        //             mesure = poel.lireResistance();
        //             SerialCom.printf("p m %d\n", mesure);
        //             break;
        //         case 'e': //état du poelon (renvoie déployé ou rétracté par message)
        //             etat = poel.recupEtat();
        //             SerialCom.printf("p e %d\n", etat);
        //             break;
        //         case 'p': //pousser un carré
        //             poel.pousserCarre();
        //             SerialCom.printf("p p\n"); //le carré a été poussé
        //             break;
        //         case 'a': //autopousser un carré
        //             mesure = poel.autoPush();
        //             SerialCom.printf("p a %d\n", mesure); //si 0, 1, 2, 3 -> carré non poussé | si 10, 11, 12, 13 -> carré poussé
        //             break;
        //         case 'c': //changer la couleur du mode auto
        //             nb = sscanf(buffer, "p c %d", &coul);
        //             if (nb) {
        //                 poel.setCouleur(coul);
        //                 SerialCom.printf("p c %d\n", coul);
        //             } else {
        //                 SerialCom.printf("m Err: couleur du poelon non changée.\n");
        //             }
        //             break;
        //         default:
        //             SerialCom.printf("m Err: poelon n'a pas cette commande (%c).\n", buffer[2]);
        //             break;
        //     }
        // } 
        else if (buffer[0] == 'd'){
            SerialCom.println("b a6_BRAS_AVANT 360 690 1 RW u");
            SerialCom.println("b a7_MAIN_AVANT 0 780 1 RW u");
            SerialCom.println("b a4_BRAS_ARRIERE 540 930 1 RW u");
            SerialCom.println("b a5_MAIN_ARRIERE 0 720 1 RW u");
            SerialCom.println("b p1_Pompe_1 0 1 1 RW u");
            SerialCom.println("b p2_Pompe_2 0 1 1 RW u");
            SerialCom.println("b e1_E-Vanne_1 0 1 1 RW u");
            SerialCom.println("b e2_E-Vanne_2 0 1 1 RW u");
        }
        else if (buffer[0] == 'a'){//commande Actionneur
            
            if (buffer[2]=='a'){//C'est un AX12
                int idAX12Sign, valeur;
                int params = sscanf(buffer, "a a%d %d", &idAX12Sign, &valeur);
                unsigned int idAX12 = (unsigned int) idAX12Sign;
                if (params == 2){
                    if (idAX12%2 == 0){//bras
                        AX12As.moveSpeed(idAX12, valeur, 150);
                    }
                    else{
                        AX12As.moveSpeed(idAX12, valeur, 400);
                    }
                    
                }
            }
            else if (buffer[2]=='p'){//C'est une pompe
                int idPompe,valeur;
                int params = sscanf(buffer, "a p%d %d", &idPompe, &valeur);
                if (params == 2){
                    int pSelect=0;
                    if (idPompe==1){
                        pSelect=POMPE1;
                    }
                    else if(idPompe==2){
                        pSelect=POMPE2;
                    }
                    if (pSelect!=0){
                        if (valeur==0){
                            digitalWrite(pSelect,LOW);
                        }
                        else{
                            digitalWrite(pSelect,HIGH);
                        }
                    }
                    
                }
            }
            else if (buffer[2]=='e'){//C'est une electro-vanne
                int idVanne,valeur;
                int params = sscanf(buffer, "a e%d %d", &idVanne, &valeur);
                if (params == 2){
                    ElecVanne* eVSelect=&ev1;
                    int recon = 0;
                    if (idVanne==1){
                        eVSelect=&ev1;
                        recon++;
                    }
                    else if(idVanne==2){
                        eVSelect=&ev2;
                        recon++;
                    }
                    if (recon){
                        if (valeur==0){
                            eVSelect->putOff();
                        }
                        else{
                            eVSelect->putOn();
                        }
                    }
                    
                }
            }
            
        }
        else if (buffer[0] == 't') //test
        {
            int test_index;
            int params = sscanf(buffer, "t %d", &test_index);
        }
    }

    //Récupération des derniers messages sur le buffer SerialCom et traitement
void Comm::update(){
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
}
void Comm::spam_odom() {
        SerialCom.print("r "); //Odométrie moteur
        SerialCom.print(odom.get_x());
        SerialCom.print(" ");
        SerialCom.print(odom.get_y());
        SerialCom.print(" ");
        SerialCom.println(odom.get_theta());
        //#define or undef
        #undef COMM_SPAM_SPEED
        #ifdef COMM_SPAM_SPEED
            SerialCom.print("o "); //Odométrie moteur
            SerialCom.print(Odometry::get_speed_motor());
            SerialCom.print(" ");
            SerialCom.println(Odometry::get_omega_motor());
        #endif
}



