#include <iostream>
#include "StateMachine.h"

using namespace std;

int main() {

    printf("oi");

    FILE *input = fopen("code.txt", "r");
    FILE *output = fopen("newCode.txt", "w");
    char carac;
    StateMachine stateMachine;
    stateMachine = StateMachine();

    while( fscanf(input, "%c", &carac)){
        stateMachine.goToNextState(carac);
        if (stateMachine.getCurrentState() == 1)
            fprintf(output, "%c", carac);
        else if (stateMachine.getCurrentState() == 2) {
            fscanf(input, "%c", &carac);
            stateMachine.goToNextState(carac);

            if (stateMachine.getCurrentState() == 1)
                fprintf(output, "/%c", carac);
        }
    }

    return 0;
}