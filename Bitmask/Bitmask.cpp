#include "Bitmask.h"
#include <algorithm>
#include <climits>
#include <cstring> //for memset function
#include <iostream>
#include <stdlib.h>

Bitmask::Bitmask(int _n, std::vector< std::vector<int> > vec) : n(_n), dist(vec) {
    // for(auto i : dist){
    //     for(auto j : i) cout << j << " ";
    //     cout << endl;
    // }
    memset(parent, -1, sizeof parent);
    memset(dp, -1, sizeof dp);
}

void Bitmask::solveTSP(){
    //TODO: set bestPath
    bestPathCost = solverTSP(1, 0);
}

void Bitmask::getPath(std::ofstream &output){
    std::vector<int> path;
    int cur_node = 0;
    int cur_mask = 1;
    int flag = 0;
    do {
        if(abs(cur_node) < n) {
            if(flag) output << ", ";
            flag = 1;
            output << cur_node;
            path.push_back(cur_node);
        }
        else break;
        cur_node = parent[cur_mask][cur_node];
        cur_mask = cur_mask | (1 << cur_node);
    } while(cur_node != -1);
    if(path.size() == n) output << ", " << path[0];
}

long long Bitmask::solverTSP(long long mask, long long pos){
    if(mask == ((1 << n) - 1)){
        return dist[pos][0];
    } 
    if(dp[mask][pos] != -1) return dp[mask][pos];

    long long ans = INT_MAX;
    for(int i=0;i<n;i++){
        if((mask&(1 << i)) == 0){
            long long aux = dist[pos][i] +  solverTSP(mask|(1<<i), i);
            if(aux < ans){
                ans = aux;
                parent[mask][pos] = i;
            }
        }
    }
    return dp[mask][pos] = ans;
}