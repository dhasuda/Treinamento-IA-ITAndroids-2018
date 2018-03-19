//
// Created by Davi Grossi Hasuda on 06/04/17.
//

#include "Population.h"

Population::Population(int populationSize, bool init) {
    if (init) {
        for (int i = 0; i < populationSize; i++) {
            Individual newIndividual = Individual();
            saveIndividual(newIndividual);
        }
    }
}


int Population::size() {
    return (int)individuals.size();
}

void Population::saveIndividual(Individual newIndividual) {
    individuals.push_back(newIndividual);
}

Individual Population::getIndividual(int index) {
    return individuals[index];
}

Individual Population::getFittest() {
    Individual fittest = individuals[0];
    for (int i = 0; i < size(); i++) {
        if (fittest.getFitness() < individuals[i].getFitness()) {
            fittest = getIndividual(i);
        }
    }
    return fittest;
}
