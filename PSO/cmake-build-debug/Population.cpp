//
// Created by Davi Grossi Hasuda on 19/03/2018.
//

#include "Population.h"

Population::Population(int numberOfParticles, int xSize, vector<double> lowerBound, vector<double> upperBound) {
    this->lowerBound = lowerBound;
    this->upperBound = upperBound;
    for (int i=0; i<numberOfParticles; i++) {
        vector<double> position;
        for (int j=0; j<xSize; j++) {
            double random = (double)rand() / RAND_MAX;
            position.push_back(lowerBound[j] + random*(upperBound[j] - lowerBound[j]));
        }
        Particle newParticle = Particle(position);
        particles.push_back(newParticle);
    }
    globalBest = particles[0].getPersonalBest();
    globalBestPosition = particles[0].getPersonalBestPosition();

    for (int i=0; i<particles.size(); i++) {
        if (particles[i].getPersonalBest() > globalBest) {
            globalBest = particles[i].getPersonalBest();
            globalBestPosition = particles[i].getPersonalBestPosition();
        }
    }
}

void Population::runOneIteration() {

    int w = 1;
    int c1 = 2;
    int c2 = 2;

    for (int i=0; i<particles.size(); i++) {
        // TODO: Move particles
    }

}

double Population::getGlobalBest() {
    return this->globalBest;
}

vector<double> Population::getGlobalBestPosition() {
    return this->globalBestPosition;
}
