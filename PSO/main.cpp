#include "pso.cpp"
#include <iostream>
#include <utility>
#include <set>
#include <climits>
#include <cmath>

int main(){

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

    int swarmSize = 5;
    int dimensions = adjList.size()-1;
    Function fitness(
        [adjList, adjListCost](std::vector<double> pos) -> double {
            std::set<int> visited;
            int result = 0;
            int oldPos = 0;
            for(int i = 0; i < pos.size(); ++i){
                if(!visited.insert(oldPos).second) return INT_MAX;
                int currentPos = adjList[oldPos][(int)round(pos[i]) % adjList[oldPos].size()];
                result += adjListCost[oldPos][(int)round(pos[i]) % adjList[oldPos].size()];
                oldPos = currentPos;
            }
            if(!visited.insert(oldPos).second) return INT_MAX;
            return result;
        }
    );
    std::vector<double> lb(dimensions, 0), ub(dimensions, nodeCount-1);
    Particle p = particleSwarm(dimensions, swarmSize, fitness, lb, ub);
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
    } else{
        std::cout << "Satisfying result could not be reached" << std::endl;
    }
}