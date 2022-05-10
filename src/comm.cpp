#include "comm.h"

#include <Arduino.h>
#include "odom.h"
#include "motor.h"
#include "poelon.h"
#include "AX12A.h"
#include "elecvannes.h"
#include "DisplayController.h"
#include "main.h"
#include "macros.h"
#include "config.h"
#include "integration_test.h"

// recap des messages en entrée:
// v <int> <int>: commande de vitesse <linéaire * 1000> <omega * 1000>
// s : arrêt du robot
// a <id> <int> : ordre à un actionneur. id est deux caractères,
//       le premier donnant le type d'actionneur
//                      (a pour AX12A, p pour pompe, e pour electroVanne, s pour servo, d pour le display)
//       le deuxième est un chiffre d'identification.
// d : demande de description des actionneurs. Le robot répond une seule fois
// k: reset l'entier sentDescr
// g [o/v] <int> <int> : changement des valeurs des PIDs (kp et ki)

// recap des messages en sortie:
// m <string>
// r <int> <int> <int> <int> <int>: odométrie moteur <x> <y> <théta> <v> <omega>
// b <string> <int> <int> <int> [R/RW] <string>: déclaration d'un actionneur (RW) ou d'un capteur (R).
// c <string> <int> : retour de capteur

// Analyse des informations contenues dans les messages SerialCom

void Comm::parse_data()
{
    if (buffer[0] == 's')
    { // Stop
        motor.stop();
        SerialCom.println("m Stopping robot.");
    }
    else if (buffer[0] == 'g')
    {
        int kp, ki;
        char c;
        int nbRec = sscanf(buffer, "g %c %d %d", &c, &kp, &ki);
        if (nbRec == 3)
        {
            motor.set_PID(c, kp, ki);
            SerialCom.println("m Gains changed.");
        }
        else
        {
            SerialCom.println("m Error: wrong number of arguments.");
        }
    }
    else if (buffer[0] == 'v')
    { // Vitesse
        int x, omega;
        int nb = sscanf(buffer, "v %d %d", &x, &omega);
        if (nb == 2)
        {
            motor.set_cons(static_cast<float>(x), static_cast<float>(omega) / 10.f);
        }
    }
    else if (buffer[0] == 'k')
    {
        sentDescr = 0;
    }
    else if (buffer[0] == 'd')
    {
        if (sentDescr == 0)
        {
            SerialCom.println("b ma 0 1 1 RW u");
            SerialCom.println("b mc 0 1 1 RW u");
            SerialCom.println("b me 0 1 1 RW u");
            SerialCom.println("b mg 0 1 1 RW u");
            SerialCom.println("b mb 0 1 1 RW u");
            SerialCom.println("b md 0 1 1 RW u");
            SerialCom.println("b mf 0 1 1 RW u");
            SerialCom.println("b mh 0 1 1 RW u");
            SerialCom.println("b d 0 9999 1 RW u");
            SerialCom.println("b a6 360 690 1 RW u");
            SerialCom.println("b a7 0 900 1 RW u");
            SerialCom.println("b a4 540 930 1 RW u");
            SerialCom.println("b a5 0 900 1 RW u");
            SerialCom.println("b p1 0 1 1 RW u");
            SerialCom.println("b p2 0 1 1 RW u");
            SerialCom.println("b e1 0 1 1 RW u");
            SerialCom.println("b e2 0 1 1 RW u");
            SerialCom.println("b s1 50 140 10 RW °");
            SerialCom.println("b LR 0.0 99.0 0.1 R hOhm");
            sentDescr = 1;
        }
    }
    else if (buffer[0] == 'a')
    { // commande Actionneur

        if (buffer[2] == 'a')
        { // C'est un AX12
            int idAX12Sign, valeur;
            int params = sscanf(buffer, "a a%d %d", &idAX12Sign, &valeur);
            unsigned int idAX12 = (unsigned int)idAX12Sign;
            if (params == 2)
            {
                if (idAX12 % 2 == 0)
                { // bras
                    AX12As.moveSpeed(idAX12, valeur, 150);
                }
                else
                {
                    AX12As.moveSpeed(idAX12, valeur, 400);
                }
            }
        }
        else if (buffer[2] == 'p')
        { // C'est une pompe
            int idPompe, valeur;
            int params = sscanf(buffer, "a p%d %d", &idPompe, &valeur);
            if (params == 2)
            {
                int pSelect = 0;
                if (idPompe == 1)
                {
                    pSelect = POMPE1;
                }
                else if (idPompe == 2)
                {
                    pSelect = POMPE2;
                }
                if (pSelect != 0)
                {
                    if (valeur == 0)
                    {
                        digitalWrite(pSelect, LOW);
                    }
                    else
                    {
                        digitalWrite(pSelect, HIGH);
                    }
                }
            }
        }
        else if (buffer[2] == 'e')
        { // C'est une electro-vanne
            int idVanne, valeur;
            int params = sscanf(buffer, "a e%d %d", &idVanne, &valeur);
            if (params == 2)
            {
                ElecVanne *eVSelect = &ev1;
                int recon = 0;
                if (idVanne == 1)
                {
                    eVSelect = &ev1;
                    recon++;
                }
                else if (idVanne == 2)
                {
                    eVSelect = &ev2;
                    recon++;
                }
                if (recon)
                {
                    if (valeur == 0)
                    {
                        eVSelect->putOff();
                    }
                    else
                    {
                        eVSelect->putOn();
                    }
                }
            }
        }
        else if (buffer[2] == 's')
        { // c'est un servo
            int idServ = 0;
            int valeur = 0;
            int params = sscanf(buffer, " a s%d %d", &idServ, &valeur);
            if (params == 2)
            {
                if (idServ == 1)
                {
                    poel.changerEtat(valeur);
                }
            }
        }
        else if (buffer[2] == 'd')
        { // c'est un display 7 segments
            int val = -1;
            int params = sscanf(buffer, "a d %d", &val);
            if (params == 1)
            {
                afficheur.setNbDisplayed(val);
            }
        }
        else if (buffer[2]== 'r'){
            //On demende la valeur de la resistance depuis le haut niveau
            float res = poel.lireResistance();
            int retourn = 0;
            if (digitalRead(COLOR)==LOW){//On est côté Violet
                if (res>0.2 && res <0.7){//On veux une valeur à 0.47
                    retourn =1;
                }
            }
            else{//On est côté Jaune
                if (res>0.7 && res <2.0){//On veux une valeur à 1
                    retourn =1;
                }
            }
            SerialCom.print ("c LR ");
            SerialCom.println (retourn);
        }
        else if (buffer[2] == 'm')
        { // c'est une macro
            switch (buffer[3])
            {
            case 'a':
                bras_main_pompe_ev_av.handleEvent(TRIGGER_GET);
                break;

            case 'b':
                bras_main_pompe_ev_ar.handleEvent(TRIGGER_GET);
                break;

            case 'c':
                bras_main_pompe_ev_av.handleEvent(TRIGGER_INSTORE);
                break;

            case 'd':
                bras_main_pompe_ev_ar.handleEvent(TRIGGER_INSTORE);
                break;

            case 'e':
                bras_main_pompe_ev_av.handleEvent(TRIGGER_FROMSTORE);
                break;

            case 'f':
                bras_main_pompe_ev_ar.handleEvent(TRIGGER_FROMSTORE);
                break;

            case 'g':
                bras_main_pompe_ev_av.handleEvent(TRIGGER_PUT);
                break;

            case 'h':
                bras_main_pompe_ev_ar.handleEvent(TRIGGER_PUT);
                break;

            /*case 'g':
                //deposerAngle(true);
                break;

            case 'h':
                //deposerAngle(false);
                break;*/

            default:
                SerialCom.println("m macro inconnue");
            }
        }
    }
    else if (buffer[0] == 'i') // Integration test
    {
        int test_index;
        //char* splitted_buffer = strtok(buffer," ");
        char* test_name;
        memcpy(test_name, buffer+2, strlen(buffer)-1); //TODO : a tester c'est une suggestion du copilote
        integration_test::launch_test(test_name);
    }
}

//Report du démarage
void Comm::reportStart(){
    for (int i=0;i<3;i++){
        SerialCom.println("c TI 42");
    }
}

// Récupération des derniers messages sur le buffer SerialCom et traitement
void Comm::update()
{
    int a = SerialCom.available(); // nombre de charactères à lire sur le buffer SerialCom
    if (a)
    {
        for (int i = 0; i < a; i++)
        {
            char c = SerialCom.read();
            if (c == '\n')
            {
                buffer[buf_index] = '\0';
                parse_data();
                buf_index = 0;
            }
            else if (c == '\r')
            {
            }
            else
            {
                buffer[buf_index] = c;
                buf_index++;
            }
        }
    }
}
void Comm::spam_odom()
{
    SerialCom.print("r "); // Odométrie moteur
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
    SerialCom.print("o "); // Odométrie moteur
    SerialCom.print(Odometry::get_speed_motor());
    SerialCom.print(" ");
    SerialCom.println(Odometry::get_omega_motor());
#endif
}

void Comm::spamValeursCapt()
{
    SerialCom.print("c s1 ");
    SerialCom.println(poel.recupEtat());
    SerialCom.print("c a4 ");
    SerialCom.println(AX12As.readPosition((uint8_t)4));
    SerialCom.print("c a5 ");
    SerialCom.println(AX12As.readPosition((uint8_t)5));
    SerialCom.print("c a6 ");
    SerialCom.println(AX12As.readPosition((uint8_t)6));
    SerialCom.print("c a7 ");
    SerialCom.println(AX12As.readPosition((uint8_t)7));
    SerialCom.print("c e1 ");
    SerialCom.println(ev1.getState());
    SerialCom.print("c e2 ");
    SerialCom.println(ev2.getState());
    SerialCom.print("m Color = ");
    SerialCom.println(color);
}

void Comm::reportStateMachineStates(int av, int ar){
    SerialCom.print("c mv ");//état state machine avant
    SerialCom.println(av);
    SerialCom.print("c mr ");//état state machine arrière
    SerialCom.println(ar);
    SerialCom.print("c hv ");//contenu main avant
    SerialCom.println(av_hand_content);
    SerialCom.print("c hr ");//contenu main arrière
    SerialCom.println(ar_hand_content);
    SerialCom.print("c sc ");//contenu réserve
    SerialCom.println(store_content);
}