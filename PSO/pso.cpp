#include "./particle/particle.h"
#include "./random/random_engine.h"
#include <stdbool.h>
#include <iostream>
#include <functional>

#define MAX_ITER 1000

typedef std::function<double(std::vector<double>)> Function;

double omega(int t){ // Omega changes linearly during the execution
    double currentOffset = (double) t/MAX_ITER;
    return 0.5 + (0.9 - 0.5)*currentOffset; //increasing inertia weight
    //return 0.9 - (0.9 - 0.5)*currentOffset; //decreasing inertia weight
}

std::vector<Particle> swarm;
Particle gBest;

Particle particleSwarm(int dimensions, int swarmSize, Function fitness, std::vector<double> lb, std::vector<double> ub){
    // Initialize swarm with random positions and velocities and set initial global best particle
    for(int i = 0; i < swarmSize; ++i) {
        std::vector<double> pos;
        std::vector<double> vel;
        for(int j = 0; j < dimensions; ++j) {
            pos.push_back(uniformRandom(0, 1));
            vel.push_back(uniformRandom(0, 1));
        }
        Particle p(pos, vel, lb, ub);
        if(i == 0 || fitness(p.getPos()) < fitness(gBest.getPos())){
            gBest = p;
        }
        swarm.push_back(p);
    }
    
    // Variables used to limit meaningless iterations (stop if gBest didn't change in 3 iterations)
    int didntUpdate = 0;
    bool updated = true;
    for(int i = 0; i < MAX_ITER && didntUpdate < 1000; ++i){
        for(auto p : swarm){
            // Update Velocity and Position according to the PSO algorithm
            p.move(i, omega(i), gBest);

            // Update local best position for particle p according to fitness
            if(fitness(p.getPos()) < fitness(p.getBestPos())){
                p.updateBestPos();
                
                // Update global best position if current position of p is better than that
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
    return gBest;
}