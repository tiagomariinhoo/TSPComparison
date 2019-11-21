#include "./particle/particle.h"
#include "./random/random_engine.h"
#include <stdbool.h>
#include <exception>
#include <iostream>

#define MAX_ITER 1000
#define SWARM_SIZE 5
#define DIMENSIONS 2

double omega(int t){ // Omega changes linearly during the execution
    double currentOffset = (double) t/MAX_ITER;
    return 0.5 + (0.9 - 0.5)*currentOffset; //increasing inertia weight
    //return 0.9 - (0.9 - 0.5)*currentOffset; //decreasing inertia weight
}

double fitness(std::vector<double> pos){ //TODO: edit this fitness function to solve TSP
    double x = pos[0];
    double y = pos[1];
    return (1-x)*(1-x) + 100*(y - x*x)*(y - x*x);
}

std::vector<Particle> swarm;
std::vector<double> lb(DIMENSIONS, -100), ub(DIMENSIONS, 100);
Particle gBest;
static bool initialized = false;

void init(){
    for(int i = 0; i < SWARM_SIZE; ++i) {
        std::vector<double> pos;
        std::vector<double> vel;
        for(int j = 0; j < DIMENSIONS; ++j) {
            pos.push_back(uniformRandom(0, 1));
            vel.push_back(uniformRandom(0, 1));
        }
        Particle p(pos, vel, lb, ub);
        if(i == 0 || fitness(p.getPos()) < fitness(gBest.getPos())){
            gBest = p;
        }
        swarm.push_back(p);
    }
    initialized = true;
}

void run(){
    if(!initialized){
        init();
    }
    int didntUpdate = 0;
    bool updated = true;
    for(int i = 0; i < MAX_ITER && didntUpdate < 2; ++i){
        for(auto p : swarm){
            p.move(i, omega(i), gBest);
            if(fitness(p.getPos()) < fitness(p.getBestPos())){
                p.updateBestPos();
                if(fitness(p.getPos()) < fitness(gBest.getPos())){
                    gBest = p;
                    updated = true;
                }
            }
        }
        if(!updated) ++didntUpdate;
        else didntUpdate = 0;
        updated = false;
        std::cout << "Iteration: "  << i+1 << ", Best Fitness: " << fitness(gBest.getPos()) << ", Omega: " << omega(i) << std::endl;
    }
}