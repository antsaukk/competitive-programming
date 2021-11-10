#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include <cmath>
#include <utility>

// https://cses.fi/381/task/A - string matching


void solve(string& str, size_t q) {
	vector<int> a(q);
	for(size_t i = 0; i < q; i++) {
		string pattern; 
		cin >> pattern;
		auto f = str.find(pattern);
		if (f!=string::npos) {
			a[i] = 1;
		}
	}
	
	for(auto s : a) {
		if (s) {
			cout << "YES\n";
		} else { cout << "NO\n"; }
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	string str;
	size_t q; 
	cin >> str;
	cin >> q;

	solve(str, q);

	return 0;
}