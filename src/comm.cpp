#include "comm.h"

#include <Arduino.h>
#include "odom.h"
#include "motor.h"
#include "poelon.h"
#include "AX12A.h"
#include "elecvannes.h"


//recap des messages en entrée:
//v <int> <int>: commande de vitesse <linéaire * 1000> <omega * 1000>
//s : arrêt du robot
//a <id> <int> : ordre à un actionneur. id est deux caractères, le premier donnant le type d'actionneur (a pour AX12A, p pour pompe, e pour electroVanne, s pour servo)
//                                                              le deuxième est un chiffre d'identification.
//d : demande de description des actionneurs
//g [o/v] <int> <int> : changement des valeurs des PIDs (kp et ki)




//recap des messages en sortie:
//m <string>
//p <int> <int> <int>: odométrie moteur <x> <y> <théta>
//b <string> <int> <int> <int> [R/RW] <string>: déclaration d'un actionneur (RW) ou d'un capteur (R). 
//c <string> <int> : retour de capteur



  
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
        else if (buffer[0] == 'd'){
            SerialCom.println("b a6_BRAS_AVANT 360 690 1 RW u");
            SerialCom.println("b a7_MAIN_AVANT 0 780 1 RW u");
            SerialCom.println("b a4_BRAS_ARRIERE 540 930 1 RW u");
            SerialCom.println("b a5_MAIN_ARRIERE 0 720 1 RW u");
            SerialCom.println("b p1_Pompe_1 0 1 1 RW u");
            SerialCom.println("b p2_Pompe_2 0 1 1 RW u");
            SerialCom.println("b e1_E-Vanne_1 0 1 1 RW u");
            SerialCom.println("b e2_E-Vanne_2 0 1 1 RW u");
            SerialCom.println("b s1_ServoPoelon 50 140 10 RW °");
            SerialCom.println("b Lecture_Resistance 0.0 100.0 0.1 R hOhm");
        }
        else if (buffer[0] == 'a'){//commande Actionneur
            
            if (buffer[2]=='a'){//C'est un AX12
                int idAX12Sign, valeur;
                int params = sscanf(buffer, "a a%d %d", &idAX12Sign, &valeur);
                unsigned int idAX12 = (unsigned int) idAX12Sign;
                if (params == 2){
                    if (idAX12%2 == 0){//bras
                        AX12As.moveSpeed(idAX12, valeur, 150);}
                    else{AX12As.moveSpeed(idAX12, valeur, 400);}
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
            else if (buffer[2]=='s'){
                int idServ = 0;
                int valeur = 0;
                int params = sscanf(buffer, " a s%d %d", &idServ, &valeur);
                if (params==2){
                    if (idServ ==1){poel.changerEtat(valeur);}
                }
            }
            
        }
        else if (buffer[0] == 't') //test
        {
            int test_index;
            int params = sscanf(buffer, "t %d", &test_index);
            params++;
            params--;//Ajouté pour faire dégager un warning
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
        SerialCom.print(odom.get_theta());
        SerialCom.print(" ");
        SerialCom.print(odom.get_speed_motor());
        SerialCom.print(" ");
        SerialCom.println(odom.get_omega_motor());
        //#define or undef
        #undef COMM_SPAM_SPEED
        #ifdef COMM_SPAM_SPEED
            SerialCom.print("o "); //Odométrie moteur
            SerialCom.print(Odometry::get_speed_motor());
            SerialCom.print(" ");
            SerialCom.println(Odometry::get_omega_motor());
        #endif
}

void Comm::spamValeursCapt(){
    #ifdef POELON
    SerialCom.print ("c s1_ServoPoelon ");
    SerialCom.println(poel.recupEtat());
    SerialCom.print ("c Lecture_Resistance ");
    SerialCom.println(poel.lireResistance()*10.f);
    #endif
    
}


