//
// Created by Davi Grossi Hasuda on 06/04/17.
//

#ifndef GENETIC_ALGORITHM_POPULATION_H
#define GENETIC_ALGORITHM_POPULATION_H

#include "Individual.h"
#include <vector>

class Population {
private:
    std::vector<Individual> individuals;

public:
    Population(int populationSize);
    int size();
    void saveIndividual(Individual newIndividual);
    Individual getIndividual(int index);
    Individual getFittest();

};


#endif //GENETIC_ALGORITHM_POPULATION_H
