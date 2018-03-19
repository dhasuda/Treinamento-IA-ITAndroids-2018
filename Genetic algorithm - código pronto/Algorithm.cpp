//
// Created by Davi Grossi Hasuda on 06/04/17.
//

#include "Algorithm.h"

Population Algorithm::evolvePopulation(Population pop) {
    Population newPopulation = Population(pop.size(), false);

    newPopulation.saveIndividual(pop.getFittest());

    // Crossover
    int elitismOffset;
    elitismOffset = 1;

    for (int i = elitismOffset; i < pop.size(); i++) {
        Individual indiv1 = tournamentSelection(pop);
        Individual indiv2 = tournamentSelection(pop);
        Individual newIndiv = crossover(indiv1, indiv2);
        newPopulation.saveIndividual(newIndiv);
    }

    // Mutation
    for (int i = elitismOffset; i < newPopulation.size(); i++) {
        mutate(newPopulation.getIndividual(i));
    }
    return newPopulation;
}

Individual Algorithm::crossover(Individual indiv1, Individual indiv2) {
    Individual newIndiv = Individual();
    double uniformRate = 0.5;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if ((double)rand() <= uniformRate) {
                newIndiv.setGene(indiv1.getGene(i, j), i, j);
            } else {
                newIndiv.setGene(indiv2.getGene(i, j), i, j);
            }
        }
    }
    return newIndiv;
}

void Algorithm::mutate(Individual indiv) {
    double mutationRate = 0.015;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if ((double)rand() <= mutationRate) {
                int gene = 1 + (rand() % (9 - 1 + 1)); // Random integer between 1 and 9
                indiv.setGene(gene, i, j);
            }
        }
    }
}

// Select individuals for crossover
Individual Algorithm::tournamentSelection(Population pop) {
    int tournamentSize = 5;

    Population tournament = Population(tournamentSize, false);
    for (int i = 0; i < tournamentSize; i++) {
        int randomId = (rand() % (pop.size() + 1)); // Random integer between 0 and pop.size()
        tournament.saveIndividual(pop.getIndividual(randomId));
    }
    return tournament.getFittest();
}