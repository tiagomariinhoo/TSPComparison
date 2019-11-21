#include <bits/stdc++.h>
#include "Bitmask.h"

using namespace std;

int main(int argc, char** argv){

	vector< vector<int> > vec;

	Bitmask a(5, vec);
	a.printTest();

	cout << a.getSize() << endl;

	return 0;
}