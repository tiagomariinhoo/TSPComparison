#include "Bitmask.h"
#include <iostream>
#include <climits>
#include <ctime>
#include <fstream>

using namespace std;

ofstream output("output.json", ios_base::trunc);

/**WINDOWS
 * To compile: g++ -std=c++17 Main.cpp Bitmask.cpp -o main
 * To run: main < in
 */

int main(int argc, char** argv){
	int nodeCount, edgeCount;
	cin >> nodeCount >> edgeCount;
	vector<int> aux(nodeCount, INT_MAX);
	vector< vector<int> > vec(nodeCount, aux);
	
	for(int i = 0; i < edgeCount; ++i){
		int a, b, c;
		cin >> a >> b >> c;
		vec[a][b] = c;
	}

	for(int i = 0; i < nodeCount; ++i){
		vec[i][i] = 0;
	}	

	Bitmask btm(vec.size(), vec);

	clock_t t = clock();
	btm.solveTSP();
	t = clock()-t;
	
	output << "{" << std::endl;
	output << "\t\"chosen_path\": [";
	btm.getPath(output);
	output << "], " << std::endl;
	output << "\t\"path_cost\": " << btm.bestPathCost << std::endl;
    output << "}" << std::endl;
    output.close();

	return 0;
}