#include "particle.h"
#include <string>
#include <iostream>
#include "../random/random_engine.h"

double simpleBounds(double lb, double val, double ub){
    val = lb > val ? lb : val;
    val = ub < val ? ub : val;
    return val;
}

void Particle::move(double omega, Particle gBest){
    for(int i = 0; i < velocity.size(); ++i){
        velocity[i] = omega*velocity[i] + C1*uniformRandom(0, 1)*(bestPos[i] - position[i]) + C2*uniformRandom(0, 1)*(gBest.getPos()[i] - position[i]);
        position[i] = position[i] + velocity[i];
        position[i] = simpleBounds(lowerBoundaries[i], position[i], upperBoundaries[i]);
    }
}