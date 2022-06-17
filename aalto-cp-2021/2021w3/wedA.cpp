#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	size_t n;
	cin >> n;

	bool all = 0;
	vector<int> denoms(n, 0);
	for(size_t i = 0; i < n; i++) {
		cin >> denoms[i];
		all = (denoms[i] == 1);
		if (all) break;
	}

	if (all) {
		cout << "ALL";
		return 0;
	} else {
		cout << 1;
	}

	return 0;
}