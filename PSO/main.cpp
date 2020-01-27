#include "pso.cpp"
#include <iostream>
#include <set>
#include <climits>
#include <cmath>
#include <ctime>
#include <algorithm>

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
    int startPos = 0;
    int bestStartPos = 0;
    Function fitness;
    fitness = [adjList, adjListCost, &startPos, &bestStartPos, &fitness](std::vector<double> pos) -> double {
        if(startPos >= adjList.size()){
            startPos = 0;
            return INT_MAX;
        }
        std::vector<int> visited(adjList.size());
        int result = 0;
        int oldPos = startPos;
        for(int i = 0; i < pos.size(); ++i){
            if(visited[oldPos] == 1){
                //if this is a bad attempt, try with another starting position
                startPos += 1;
                return fitness.operator()(pos);
            }
            visited[oldPos] = 1;
            int val = (int)round(pos[i]) % adjList[oldPos].size();
            int currentPos = adjList[oldPos][val];
            result += adjListCost[oldPos][val];
            oldPos = currentPos;
        }
        if(visited[oldPos] == 1){
            //if this is a bad attempt, try with another starting position
            startPos += 1;
            return fitness.operator()(pos);
        }

        std::vector<int>::const_iterator startPosIt = std::find(adjList[oldPos].begin(), adjList[oldPos].end(), startPos);
        if(startPosIt != adjList[oldPos].end()){
            //go back to the initial position, if there's a path leading there
            int startPosLoc = std::distance(adjList[oldPos].begin(), startPosIt);
            result += adjListCost[oldPos][startPosLoc];
        } else {
            //if we can't return to the start position from the last position, try with another starting position
            startPos += 1;
            return fitness.operator()(pos);
        }

        bestStartPos = startPos;
        startPos = 0;
        return result;
    };
    
    //Running and benchmarking PSO
    clock_t t = clock();
    Particle p = particleSwarm(dimensions, swarmSize, fitness, lb, ub);
    t = clock()-t;

    //Printing the results of PSO
    if(fitness(p.getPos()) != INT_MAX){
        std::cout << "Chosen Path: ";
        std::vector<int> resultArray;
        std::vector<double> pos = p.getPos();
        int oldPos = bestStartPos;
        std::cout << oldPos;
        for(int i = 0; i < pos.size(); ++i){
            int currentPos = adjList[oldPos][(int)round(pos[i]) % adjList[oldPos].size()];
            oldPos = currentPos;
            std::cout << ", " << oldPos;
        }
        std::cout << ", " << bestStartPos;
        std::cout << std::endl;
        std::cout << "Path's Cost: " << fitness(pos) << std::endl;
    } else{
        std::cout << "Satisfying result could not be reached" << std::endl;
    }

    //Printing the benchmarking results
    std::cout << t << " Clock cicles (" << ((double)t)/CLOCKS_PER_SEC << " seconds)" << std::endl;
}