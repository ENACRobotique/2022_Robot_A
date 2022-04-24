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
        u_int32_t lastTransition;
        int state;
        std::vector<State> stateList;
        std::vector<int> eventQueue;

    public:
        StateMachine(std::vector<State> states) {
            stateList = states;
            eventQueue = {};
            state = 0;
            lastTransition = millis();
            stateList[state].enterAction();
        };

        void handleEvent(int event){
            int newState = stateList[state].manualTransition(event);
            if (newState == -2){
                eventQueue.insert(eventQueue.begin(), event);
            } else if (newState != -1){
                state = newState;
                lastTransition = millis();
                stateList[state].enterAction();
            }
        };

        void checkAutoTransitions(){
            u_int32_t st_auto_d = stateList[state].autoDuration();
            if (st_auto_d >= 0){ //check auto timed transition
                if (millis() > st_auto_d +  lastTransition){
                    int newState = stateList[state].autoTransition();
                    if (newState != -1){
                        state = newState;
                        lastTransition = millis();
                        stateList[state].enterAction();
                    }
                }
            } else if (eventQueue.size() > 0){ //if nothing was done, try to execute a queued event
                int queued_evt = eventQueue[eventQueue.size()];
                int newState = stateList[state].manualTransition(queued_evt);
                if (newState != -2){
                    if (newState == -1){
                        eventQueue.pop_back();
                    } else if (newState > -1){
                        state = newState;
                        lastTransition = millis();
                        stateList[state].enterAction();
                    }
                }
            }
        };

        int current_state(){
            return state;
        };

};

#endif //STATE_MACHINE