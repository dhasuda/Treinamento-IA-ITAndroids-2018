#include <iostream>

#include "Algorithm.h"
#include "Individual.h"
#include "Population.h"

int main() {

    int populationSize = 50;
    Algorithm algorithm;
    Population currentPopulation = Population(populationSize, true);

    Individual completeGame = currentPopulation.getFittest();
    int bestFit = completeGame.getFitness();

    int generation = 1;

    while (bestFit < 1000) {
        //currentPopulation.~Population();
        currentPopulation = algorithm.evolvePopulation(currentPopulation);
        completeGame = currentPopulation.getFittest();
        bestFit = completeGame.getFitness();

        // Debug
        printf("Generation: %d    Fit: %d\n", generation, bestFit);
        generation++;
        // End debug

    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d   ", completeGame.getGene(i, j));
        }
        printf("\n");
    }

    return 0;
}