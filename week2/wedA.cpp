#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

int main() {
	size_t n, k; 
	cin >> n >> k;

	int r = 0;
	int c = 0;
	int inf = n+1; 
	vector<int> coord_max(n, -inf);
	vector<int> coord_min(n, inf);
	for (size_t i = 0; i < k; i++) {
		cin >> r >> c;
		size_t ind = r - 1;
		coord_max[ind] = coord_max[ind] < c ? c : coord_max[ind];
		coord_min[ind] = coord_min[ind] > c ? c : coord_min[ind];
	}

	int L = 1;
	for (size_t i = 0; i < n; i++) {
		if (coord_min[i] != inf && coord_max[i] != -inf){
			L = max(L, abs(coord_max[i] - coord_min[i]) + 1);
		}
		
	}

	cout << L;
	return 0;
}