#include <iostream>
#include "cmake-build-debug/Population.h"

int main() {

    vector<double> lowerBound;
    lowerBound.push_back(-1.0);
    lowerBound.push_back(-1.0);

    vector<double> upperBound;
    upperBound.push_back(1.0);
    upperBound.push_back(1.0);

    Population pop = Population(100, 2, lowerBound, upperBound);

    printf("Initial global best: %lf\n", pop.getGlobalBest());

   // TODO: run some iterations

    printf("Final global best: %lf\n", pop.getGlobalBest());

    return 0;
}