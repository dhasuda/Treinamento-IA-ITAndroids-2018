//
// Created by Davi Grossi Hasuda on 06/04/17.
//

#include "Algorithm.h"

Population Algorithm::evolvePopulation(Population pop) {
    //TODO
}

Individual Algorithm::crossover(Individual indiv1, Individual indiv2) {
    //TODO
}

void Algorithm::mutate(Individual indiv) {
    //TODO
}

// Select individuals for crossover
Individual Algorithm::tournamentSelection(Population pop) {
    int tournamentSize = 5;

    Population tournament = Population(0);
    for (int i = 0; i < tournamentSize; i++) {
        int randomId = (rand() % (pop.size() + 1)); // Random integer between 0 and pop.size()
        tournament.saveIndividual(pop.getIndividual(randomId));
    }
    return tournament.getFittest();
}