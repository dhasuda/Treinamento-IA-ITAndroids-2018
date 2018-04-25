//
// Created by lucasmaia on 25/04/18.
//

#include "StateMachine.h"

StateMachine::StateMachine(){
    state = 1;
}

int StateMachine::getCurrentState() {
    return state;
}

void StateMachine::goToNextState(char carac) {
    int oldState = StateMachine::getCurrentState();
    switch (oldState) {
        case 1:
            if( carac == '/')
                state = 2;
            break;

        case 2:
            if( carac == '*')
                state =3;
            else if(carac=='/')
                state = 5;
            else
                state = 1;
            break;

        case 3:
            if (carac=='*')
                state = 4;
            break;
        case 4:
            if (carac=='/')
                state = 1;
            else
                state = 3;
            break;
        case 5:
            if (carac =='\n')
                state = 1;
            break;
    }
}