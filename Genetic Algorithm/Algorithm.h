//
// Created by Davi Grossi Hasuda on 06/04/17.
//

#ifndef GENETIC_ALGORITHM_ALGORITHM_H
#define GENETIC_ALGORITHM_ALGORITHM_H

#include "Individual.h"
#include "Population.h"

class Algorithm {
private:

    static Individual crossover(Individual indiv1, Individual indiv2);
    static void mutate(Individual indiv);
    static Individual tournamentSelection(Population pop);

public:
    static Population evolvePopulation(Population pop);
//    static double average = 0.21;

};


#endif //GENETIC_ALGORITHM_ALGORITHM_H
