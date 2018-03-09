//
// Created by Davi Grossi Hasuda on 06/04/17.
//

#include "Individual.h"

Individual::Individual() {
    fitness = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            genes[i][j] = 1 + (rand() % (9 - 1 + 1)); // Random integer between 1 and 9
        }
    }
    calculateFitness();
}

int Individual::getGene(int x, int y){
    return genes[x][y];
}

void Individual::setGene(int gene, int x, int y) {
    genes[x][y] = gene;
}

int Individual::getFitness() {
    if (fitness == 0) {
        fitness = calculateFitness();
    }
    return fitness;
}

int Individual::calculateFitness() {

    if (fitness == 0) {
        fitness = 1000;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {

                /* Fitness calculation */
                for (int k = i; k < 9; k++) { // Repetition within a column
                    if (genes[i][j] == genes[k][j]) fitness--;
                }
                for (int k = j; k < 9; k++) { // Repetition within a line
                    if (genes[i][j] == genes[i][k]) fitness--;
                }
                for (int k = i; k % 3 != 2; k++) { // Repetition within a square
                    for (int l = j; l % 3 != 2; l++) {
                        if (genes[i][j] == genes[k + 1][l + 1]) fitness--;
                    }
                }

            }
        }
    }

    return fitness;
}