#include <bits/stdc++.h>
#include "Bitmask.h"

using namespace std;

void read(vector<vector<int> > &vec){
	int n;
	cin >> n;
	for(int i=0;i<n;i++){
		vector<int> aux;
		for(int j=0;j<n;j++){
			int a;
			cin >> a;
			aux.push_back(a);
		}
		vec.push_back(aux);
	}
}

/**WINDOWS
 * To compile: g++ -std=c++17 Main.cpp Bitmask.cpp -o main
 * To run: main < in
 */

int main(int argc, char** argv){

	vector< vector<int> > vec;

	read(vec);
	Bitmask btm(vec.size(), vec);

	cout << btm.solverTSP(1, 0) << endl;

	return 0;
}