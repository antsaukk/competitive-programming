#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	size_t n, q;
	cin >> n >> q;

	bool all = 0;
	vector<int> seq(n);
	for(size_t i = 0; i < n; i++) {
		cin >> seq[i];
	}

	vector<int> approx(q*2);
	for(size_t i = 0; i < q*2; i+=2) {
		cin >> approx[i] >> approx[i+1];
	}

	

	return 0;
}