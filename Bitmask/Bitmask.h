#ifndef BITMASK_H
#define BITMASK_H

#include <vector>

class Bitmask {
    
    int n;
    long long dp[(15 << 1)][15];
    long long parent[(15 << 1)][15];
    std::vector< std::vector<int> > dist;
    long long solverTSP(long long mask, long long pos);

    public:
        int bestPathCost;
        std::vector<int> bestPath;

        /**
         * Constructor
         * @param1 = number of nodes
         * @param2 = Adj list
         */
        Bitmask(int n, std::vector< std::vector<int> > vec);

        void setEdges();
        void solveTSP();
        void getPath();
        int getSize(){
            return n;
        }
};

#endif