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
https://cses.fi/alon/result/4029651/
*/

#include <unordered_map>
#include <vector>
#include <iostream>
#include <limits.h>
#include <cmath>
#include <algorithm>
#include <random>

//#include "profile.h"
 
#define ui64 uint64_t
 
using namespace std;
 
template <typename T>
inline void display(T value) {
	cout << value;
}
 
template <typename T>
inline void read(vector<T>& container) {
	for (size_t i = 0; i < container.size(); i++) {
		cin >> container[i];
	}
}
 
template <typename T> 
inline T abs(T value_a, T value_b) {
	return max(value_a, value_b) - min(value_a, value_b);
}

/*
	Generate data for benchmark
*/
template <typename T>
inline void simulate_input(vector<T>& container){
	std::random_device rd;
	std::mt19937_64 randengine(rd());

	std::uniform_int_distribution<T> distr;

	for(size_t i = 0; i < container.size(); i++)
		container[i] = distr(randengine);
}

/*
	Naive solution with hash_map, simply records all the differences between sequence members
	and chooses minimum, works in O(n^2)
*/
template <typename T>
void solve_naive(vector<T>& container, size_t n) {
	T INF = numeric_limits<T>::max();
	unordered_map<T, T> dp;
 
	T best_candidate = INF;
 
	for (size_t i = 0; i < n; i++) {
		if (dp[container[i]] == 0) { 
			for (size_t j = 0; j < n; j++) {
				if (container[i] != container[j]) {
					dp[container[i]] += ::abs(container[i], container[j]);
				}
			}
		}
 
		best_candidate =  best_candidate < dp[container[i]] ? best_candidate : dp[container[i]];
	}
 
	display(best_candidate);
}

/*
	Dynamic programming solution, creates dynamic programming table and memorizers the resuls
	compute in pass i-1 then to use in pass i. Works in O(nlogn)
*/
template <typename T>
void solve_dp(vector<T>& container, size_t n) {
	T INF = numeric_limits<T>::max();
 
	vector<T> dp(n);
 
	T current_candidate = 0;
	T best_candidate    = INF;
 
 
	for (size_t i = 0; i < n; i++) {
		dp[i]		  += ::abs(container[i], container[0]);
		current_candidate += ::abs(container[i], container[0]);
	}
	best_candidate   = best_candidate < current_candidate ? best_candidate : current_candidate;
 
	for (size_t i = 1; i < n; i++) {
 
		current_candidate += dp[i];
 
		for (size_t j = i + 1; j < n; j++) {
			current_candidate += ::abs(container[i], container[j]);
			dp[j]       	  += ::abs(container[i], container[j]);

		}
 
		best_candidate    = best_candidate < current_candidate ? best_candidate : current_candidate;
		current_candidate = 0;
	}
 
	display(best_candidate);
}

/*
	Clever solution, uses the fact the the sequence member with smallest distance to other members 
	is actually median. Works in O(n) with a really small constant :)
*/
template <typename T>
void solve_median(vector<T>& container, size_t n) {
	sort(container.begin(), container.end());
	T med = 0; 
	if (n % 2) med = container[n/2];
	else med = (container[n/2 - 1] + container[n/2])/2;
	
	T best_candidate    = 0;

	for (size_t i = 0; i < n; i++) {
		best_candidate += ::abs(container[i], med);
	}

	display(best_candidate);
}
 
// io opt
inline void desyncio() {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
}
 
int main() {
	desyncio();
	
	size_t n;
	cin >> n; 
 
	vector<ui64> v(n);
	//simulate_input(v);
	read(v); 
 	
 	{
 		//LOG_DURATION("\nRunning time: ");
 		//solve_naive(v, n);
 		//solve_dp_slow(v, n);
 		solve_median(v, n);
 	}
	
 
	return 0;
}