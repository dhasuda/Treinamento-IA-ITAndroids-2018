//
// Created by lucasmaia on 25/04/18.
//

#ifndef MAQUINADEESTADOSCOMPILADOR_STATEMACHINE_H
#define MAQUINADEESTADOSCOMPILADOR_STATEMACHINE_H


class StateMachine {
public:
    int getCurrentState();
    void goToNextState(char carac);
    StateMachine();

private:
    int state;
};


#endif //MAQUINADEESTADOSCOMPILADOR_STATEMACHINE_H
