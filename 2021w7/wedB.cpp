#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

//https://cses.fi/379/task/B - sliding median

using namespace std;

void solve(int n, int k) {
	vector<int> vals(n);
	for(int i = 0; i < n; i++) {
		int num;
		cin >> num;
		vals[i] = num;
	}

	for(int i = 0; i < n-k+1; i++) {
		vector<int> sw(k);
		for(int j = max(0, i-k); j < min(i+k, n); j++) {
			sw.push_back(vals[j]);
		}
		sort(sw.begin(), sw.end());
		double med = 0;
		if (sw.size() % 2==1) {
			nth_element(sw.begin(), sw.begin() + sw.size()/2, sw.end());
			med = sw[sw.size()/2];
		} else {
			nth_element(sw.begin(), sw.begin() + sw.size()/2, sw.end());
			double m1 = sw[sw.size()/2];
			nth_element(sw.begin(), sw.begin() + sw.size()/2 - 1, sw.end());
			double m2 = sw[sw.size()/2-1];
			med = min(m1, m2);
		}
		cout << med << " ";
	}
}


int main() {
	int n, k;
	cin >> n >> k; 
	solve(n, k);
	return 0;
}