#include "pso.cpp"
#include <iostream>
#include <utility>
#include <set>
#include <climits>
#include <cmath>

int main(){

    int nodeCount, edgeCount;
    std::cin >> nodeCount >> edgeCount;
    std::vector<std::pair<int, std::pair<int, int> > > edges;
    for(int i = 0; i < edgeCount; ++i){
        int a, b, c;
        std::cin >> a >> b >> c;
        edges.push_back(std::make_pair(c, std::make_pair(a, b)));
    }

    int swarmSize = 5;
    int dimensions = nodeCount-1;
    Function fitness(
        [edges, nodeCount](std::vector<double> pos) -> double {
            std::set<int> edgesPicked;
            std::vector<int> visited;
            visited.push_back(edges[round(pos[0])].second.first); // Adds origin of the first taken edge
            int result = 0;
            for(int i = 0; i < pos.size(); ++i){
                int value = round(pos[i]);
                
                // If edge is already in the edgesPicked array or if the next edge doesn't start at the last added node
                if(!edgesPicked.insert(value).second || visited.back() != edges[value].second.first){ 
                    return INT_MAX;
                }
                visited.push_back(edges[value].second.second); // Adds destination of the currently taken edge
                result += edges[value].first;
                
            }
            if(visited.size() == nodeCount){
                return -result;
            } else return INT_MAX;
            //return (1-pos[0]*pos[0])*(1-pos[0]*pos[0]) + 100*(pos[1]-pos[0]*pos[0])*(pos[1]-pos[0]*pos[0]);
            //return pos[0]*pos[0] + pos[1]*pos[1] + 25*(sin(pos[0])*sin(pos[0]) + sin(pos[1])*sin(pos[1]));
        }
    );
    std::vector<double> lb(dimensions, 0), ub(dimensions, edgeCount-1);
    Particle p = particleSwarm(dimensions, swarmSize, fitness, lb, ub);
    
    std::cout << "Chosen Path: ";
    std::vector<double> pos = p.getPos();
    std::cout << edges[round(pos[0])].second.first;
    for(int i = 0; i < pos.size(); ++i){
        int value = round(pos[i]);
        std::cout << ", " << edges[value].second.second;
    }
    std::cout << std::endl;
}