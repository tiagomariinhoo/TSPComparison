#include "Bitmask.h"
#include <iostream>
#include <climits>
#include <ctime>

using namespace std;

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
	
	std::cout << "Chosen Path: ";
	btm.getPath();
	// string sep = "";
	// for(int i = 0; i < btm.bestPath.size(); ++i){
	// 	std::cout << sep << btm.bestPath[i];
	// 	sep = ", ";
	// }
	std::cout << std::endl;
	std::cout << "Path's Cost: " << btm.bestPathCost << std::endl;
	std::cout << t << " Clock cicles (" << ((double)t)/CLOCKS_PER_SEC << " seconds)" << std::endl;

	return 0;
}