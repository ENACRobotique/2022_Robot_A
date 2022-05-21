#ifndef STATE_MACHINE
#define STATE_MACHINE

#include <Arduino.h>
#include <vector>

class State{
    private:
        int auto_transition;
        u_int32_t auto_duration;
        void (*action)();
        int (*manual_transition)(int);

    public:
        State(int auto_tr, int auto_dur, void (*act)(), int(*man_tr)(int)){
            action = act;
            auto_transition = auto_tr;
            auto_duration = auto_dur;
            manual_transition = man_tr;
        };

        void enterAction(){
            action();
        };

        u_int32_t autoDuration(){
            return auto_duration;
        };

        int autoTransition(){
            return auto_transition;
        };

        int manualTransition(int event){ //should return -1 if event does not change state
            return manual_transition(event);
        };
};

class StateMachine {
    private:
        bool started;
        u_int32_t lastTransition;
        int state;
        std::vector<State> stateList;
        std::vector<int> eventQueue;

    public:
        StateMachine(std::vector<State> states, int start_state_id = 0) {
            started = false;
            stateList = states;
            eventQueue = {};
            state = start_state_id;
        };

        std::vector<int> getQueue(){
            return eventQueue;
        }

        void start(){
            started = true;
            lastTransition = millis();
            stateList[state].enterAction();
        }

        //do this at your own risk, should only be used if you know what you're doing
        void forceState(int state_id){
            if (started){
                state = state_id;
                lastTransition = millis();
                stateList[state].enterAction();
            } else {
                state = state_id;
            }
        }

        void handleEvent(int event){
            int newState = stateList[state].manualTransition(event);
            if (newState == -2){
                Serial2.println("queued");
                Serial2.println(event);
                eventQueue.insert(eventQueue.begin(), event);
            } else if (newState != -1){
                state = newState;
                lastTransition = millis();
                stateList[state].enterAction();
            }
        };

        bool isStarted(){
            return started;
        }

        void checkAutoTransitions(){
            u_int32_t st_auto_d = stateList[state].autoDuration();
            bool smth_done = false;
            if (st_auto_d >= 0){ //check auto timed transition
                if (millis() > st_auto_d +  lastTransition){
                    int newState = stateList[state].autoTransition();
                    if (newState != -1){
                        state = newState;
                        lastTransition = millis();
                        stateList[state].enterAction();
                        smth_done = true;
                    }
                }
            }
            if ((!smth_done) && (eventQueue.size() > 0)){ //if nothing was done, try to execute a queued event
                int queued_evt = eventQueue.back();
                eventQueue.pop_back();
                Serial2.println("dequeued");
                Serial2.println(queued_evt);
                handleEvent(queued_evt);
                /*Serial2.println("queuetest");
                int queued_evt = eventQueue[eventQueue.size()];
                int newState = stateList[state].manualTransition(queued_evt);
                if (newState != -2){
                    Serial2.println(state);
                    Serial2.println("dequeued");
                    Serial2.println(newState);
                    eventQueue.pop_back();
                    if (newState > -1){
                        Serial2.println("exec");
                        state = newState;
                        lastTransition = millis();
                        stateList[state].enterAction();
                    }
                }*/
            }
        };

        int current_state(){
            return state;
        };

};

#endif //STATE_MACHINE