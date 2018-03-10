//
// Created by Davi Grossi Hasuda on 06/04/17.
//

#ifndef GENETIC_ALGORITHM_POPULATION_H
#define GENETIC_ALGORITHM_POPULATION_H

#include "Individual.h"
#include <vector>
#include <algorithm>

class Population {
private:
    std::vector<Individual> individuals;

public:
    Population(int populationSize);
    int size();
    void saveIndividual(Individual newIndividual);
    Individual getIndividual(int index);
    Individual getFittest();
    void ordenar();
    bool comparacao(Individual indiv1, Individual indiv2);
};


#endif //GENETIC_ALGORITHM_POPULATION_H
