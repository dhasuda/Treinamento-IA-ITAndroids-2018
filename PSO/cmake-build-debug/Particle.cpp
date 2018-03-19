//
// Created by Davi Grossi Hasuda on 19/03/2018.
//

#include "Particle.h"
#include "CostFunction.h"

Particle::Particle(vector<double> position) {
    this->position = position;
    this->personalBest = CostFunction::getCost(position);
    this->personalBestPosition = position;

    vector<double> vel;
    vel.push_back(0.0);
    vel.push_back(0.0);
    this->velocity = vel;
}

double Particle::getPersonalBest() {
    return this->personalBest;
}

vector<double> Particle::getPersonalBestPosition() {
    return this->personalBestPosition;
}

void Particle::move(vector<double> velocity) {
    // TODO: move particle
}

vector<double> Particle::getPosition() {
    return this->position;
}

vector<double> Particle::getVelocity() {
    return this->velocity;
}