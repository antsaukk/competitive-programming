#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

//https://cses.fi/379/task/C - longest increasing subsequence
#define i64 int64_t

using namespace std;

void solve(int n) { //O(n^2)
	vector<i64> vals(n);
	for(int i = 0; i < n; i++) {
		int num;
		cin >> num;
		vals[i] = num;
	}

	vector<i64> L(n, 1);
	vector<i64> p(n, -1);
	int maxIndex = -1; 
	int maxLen = 1;

	for(int i = 1; i < n; i++) {
		for(int j = 0; j < i; j++) {
			if (vals[i] > vals[j] && L[i] < L[j] + 1){
				L[i] = L[j] + 1;
				p[i] = j; 
        	}
		}
		if (p[i] > maxIndex) maxIndex = p[i];
		if (L[i] > maxLen) maxLen = L[i];
	}
	cout << maxLen;	
}

void solve1(int n) { //O(n logn)
	vector<i64> vals(n);
	for(int i = 0; i < n; i++) {
		int num;
		cin >> num;
		vals[i] = num;
	}

	vector<i64> L;

	for(int i = 0; i < n; i++) {
		auto bound = lower_bound(L.begin(), L.end(), vals[i]);
		if (bound == L.end())
			L.push_back(vals[i]);
		else
			*bound = vals[i];
	}
	cout << L.size();
}


int main() {
	int n;
	cin >> n; 
	solve1(n);
	return 0;
}