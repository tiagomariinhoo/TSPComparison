#include "Bitmask.h"
#include <algorithm>
#include <climits>
#include <cstring> //for memset function
#include <iostream>

Bitmask::Bitmask(int _n, std::vector< std::vector<int> > vec) : n(_n), dist(vec) {
    // for(auto i : dist){
    //     for(auto j : i) cout << j << " ";
    //     cout << endl;
    // }
    memset(dp, -1, sizeof dp);
}

void Bitmask::solveTSP(){
    //TODO: set bestPath
    bestPathCost = solverTSP(1, 0);
}

long long Bitmask::solverTSP(long long mask, long long pos){
    if(mask == ((1 << dist.size()) - 1)){
        return dist[pos][0];
    } 
    if(dp[mask][pos] != -1) return dp[mask][pos];

    long long ans = INT_MAX;
    for(int i=0;i<n;i++){
        if((mask&(1 << i)) == 0){
            long long aux = dist[pos][i] +  solverTSP(mask|(1<<i), i);
            ans = std::min(ans, aux);
        }
    }
    return dp[mask][pos] = ans;
}