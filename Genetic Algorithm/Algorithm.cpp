//
// Created by Davi Grossi Hasuda on 06/04/17.
//

#include "Algorithm.h"

Population Algorithm::evolvePopulation(Population pop) {
    //TODO
    Population popevolved = Population(0);
    pop.ordenar();
    for (int i = 0; i<10; i++)
        popevolved.saveIndividual(pop.getIndividual(i));

    for( int i=10; i<50; i++) {
        popevolved.saveIndividual(crossover(tournamentSelection(popevolved), tournamentSelection(popevolved)));
        mutate(popevolved.getIndividual(i));
    }
}

Individual Algorithm::crossover(Individual indiv1, Individual indiv2) {
    //TODO
    Individual filho = Individual();
    for(int i=0; i < 9; i++){
        if((double)rand()<0,5){
            for(int j=0; j<9; j++)
                filho.setGene(indiv1.getGene(i, j), i, j);
        } else {
            for (int k=0; k<9; k++)
                filho.setGene(indiv2.getGene(i, k), i, k);
        }
    }

    return filho;
}

void Algorithm::mutate(Individual indiv) {
    double changes=(double)rand();
    if (average >= changes)
    {
        changes=changes*81;
        for (int i = 0; i < changes; ++i) {
            indiv.setGene(rand()%9+1, rand()%9, rand()%9);
        }
    }

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