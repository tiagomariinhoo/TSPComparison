#ifndef PATRICLE_H
#define PARTICLE_H

#include <functional>
#include <vector>

#define C1 1.5
#define C2 2.2

class Particle {
    int dimensions;
    std::vector<double> position;
    std::vector<double> velocity;
    std::vector<double> bestPos;

    std::vector<double> lowerBoundaries;
    std::vector<double> upperBoundaries;

public:

    Particle(){}

    Particle(std::vector<double> p, std::vector<double> v, std::vector<double> lb, std::vector<double> ub) 
    : dimensions(p.size()), position(p), velocity(v), bestPos(p), lowerBoundaries(lb), upperBoundaries(ub)
    {}

    void move(int time, double omega, Particle gBest);

    void updateBestPos(){
        bestPos = position;
    }

    std::vector<double> getPos(){
        return position;
    }

    std::vector<double> getBestPos(){
        return bestPos;
    }

};

#endif