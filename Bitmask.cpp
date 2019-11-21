#include <bits/stdc++.h>
#include "Bitmask.h"

using namespace std;

Bitmask::Bitmask(int _n, vector< vector<int> > vec) : n(_n), dist(vec) {
    // Bitmask::n = _n; Outra forma de fazer
} 

int Bitmask::getSize(){
    return n;
}

void Bitmask::printTest(){
    cout << "Bitmask test" << endl;
}

int Bitmask::solverTSP(int mask, int pos){
    if(mask == ((1 << n) - 1)) return dist[pos][0];
    int ans = INT_MAX;
    for(int i=0;i<n;i++){
        if((mask&(1 << i)) == 0){
            int aux = dist[pos][i] +  solverTSP(mask|(1<<i), i);
            ans = min(ans, aux);
        } 
    }
    return ans;
}