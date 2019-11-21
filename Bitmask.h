#include <bits/stdc++.h>

class Bitmask {
    public:
        int n;
        std::vector< std::vector<int> > dist;

        /**
         * Constructors
         * @param1 = number of nodes
         * @param2 = Adj list
         */
        Bitmask(int n, std::vector< std::vector<int> > vec);

        void printTest();
        void setEdges();
        int getSize();
        int solverTSP(int mask, int pos);
};