/*
There are n sticks with some lengths. Your task is to modify the sticks so that each stick has the same length.

You can either lengthen and shorten each stick. 
Both operations cost x where x is the difference between the new and original length.

What is the minimum total cost?

INPUT:
The first input line contains an integer n: the number of sticks.
Then there are n integers: p1,p2,…,pn: the lengths of the sticks.

OUTPUT:
Print one integer: the minimum total cost.

CONSTRAINTS: 
1 <= n <= 2*10^5
1 <= pi <= 10^9

RESULT:
*/

#include <vector>
#include <map>
#include <iostream>
#include <limits.h>
#include <cmath>

#define ui64 uint64_t

using namespace std;

template <typename T>
void display(T value) {
	cout << value;
}

template <typename T>
void read(vector<T>& container) {
	for (size_t i = 0; i < container.size(); i++) {
		cin >> container[i];
	}
}

template <typename T>
void solve(vector<T>& container, size_t n) {
	T INF = numeric_limits<T>::max();
	map<T, T> dp;

	T best_candidate = INF;

	for (size_t i = 0; i < n; i++) {
		if (dp[container[i]] == 0) { 
			for (size_t j = 0; j < n; j++) {
				if (container[i] != container[j]) {
					dp[container[i]] += max(container[i], container[j]) - min(container[i], container[j]);
				}
			}
		}

		best_candidate =  best_candidate < dp[container[i]] ? best_candidate : dp[container[i]];
	}

	display(best_candidate);
}

// io opt
void desyncio() {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
}

int main() {
	desyncio();
	
	size_t n;
	cin >> n; 

	vector<ui64> v(n);
	read(v); 

	solve(v, n);

	return 0;
}