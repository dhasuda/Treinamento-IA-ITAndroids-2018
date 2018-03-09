//
// Created by Davi Grossi Hasuda on 06/04/17.
//

#ifndef GENETIC_ALGORITHM_INDIVIDUAL_H
#define GENETIC_ALGORITHM_INDIVIDUAL_H

#include <cstdlib>

class Individual {
private:
    int genes[9][9];
    int fitness;

    int calculateFitness();

public:
    Individual();
    int getGene(int x, int y);
    void setGene(int gene, int x, int y);
    int getFitness();

};


#endif //GENETIC_ALGORITHM_INDIVIDUAL_H
