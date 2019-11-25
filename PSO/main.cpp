#include "pso.cpp"
#include <iostream>
#include <set>
#include <climits>
#include <cmath>
#include <ctime>

int main(){

    //Reading graph from input
    int nodeCount, edgeCount;
    std::cin >> nodeCount >> edgeCount;
    std::vector<std::vector<int> > adjList(nodeCount);
    std::vector<std::vector<int> > adjListCost(nodeCount);

    for(int i = 0; i < edgeCount; ++i){
        int a, b, c;
        std::cin >> a >> b >> c;
        adjList[a].push_back(b);
        adjListCost[a].push_back(c);
    }

    // Setting PSO parameters
    int swarmSize = 5;
    int dimensions = adjList.size()-1;
    std::vector<double> lb(dimensions, 0), ub(dimensions, nodeCount);
    Function fitness(
        [adjList, adjListCost](std::vector<double> pos) -> double {
            std::set<int> visited;
            int result = 0;
            int oldPos = 0;
            for(int i = 0; i < pos.size(); ++i){
                if(!visited.insert(oldPos).second) return INT_MAX;
                int val = (int)round(pos[i]) % adjList[oldPos].size();
                int currentPos = adjList[oldPos][val];
                result += adjListCost[oldPos][val];
                oldPos = currentPos;
            }
            if(!visited.insert(oldPos).second) return INT_MAX;
            return result;
        }
    );
    
    //Running and benchmarking PSO
    clock_t t = clock();
    Particle p = particleSwarm(dimensions, swarmSize, fitness, lb, ub);
    t = clock()-t;

    //Printing the results of PSO
    if(fitness(p.getPos()) != INT_MAX){
        std::cout << "Chosen Path: ";
        std::vector<int> resultArray;
        std::vector<double> pos = p.getPos();
        int oldPos = 0;
        std::cout << oldPos;
        for(int i = 0; i < pos.size(); ++i){
            int currentPos = adjList[oldPos][(int)round(pos[i]) % adjList[oldPos].size()];
            oldPos = currentPos;
            std::cout << ", " << oldPos;
        }
        std::cout << std::endl;
        std::cout << "Path's Fitness: " << fitness(pos) << std::endl;
    } else{
        std::cout << "Satisfying result could not be reached" << std::endl;
    }

    //Printing the benchmarking results
    std::cout << t << " Clock cicles (" << ((double)t)/CLOCKS_PER_SEC << " seconds)" << std::endl;
}