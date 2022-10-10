/*
You are given an array of n integers, and your task is to find two values (at distinct positions) whose sum is x.
 
INPUT:

The first input line has two integers n and x: the array size and the target sum.

The second line has n integers a1,a2,…,an: the array values.

OUTPUT:

Print two integers: the positions of the values.
If there are several solutions, you may print any of them. If there are no solutions, print IMPOSSIBLE.
 
CONSTRAINTS:
1 <= n <= 2*10^5
1 <= x,bi <= 10^9

EXAMPLE:

Input:
4 8
2 7 5 1

Output:
2 4

VERIFY HERE:

https://cses.fi/problemset/task/1640/

*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
 
#define READ(x) (cin >> (x))
 
using namespace std;
using big_int64 = int64_t;
 
inline void desyncio() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}
 
template <typename T>
void PrintOut(T value, string const& delimeter = "") {
	cout << value << delimeter;
}
 
template <typename T>
void ReadStream(vector<T>& container) {
	for (size_t i = 0; i < container.size(); i++) {
		T x; 
		READ(x);
 
		container[i] = x;
	}
}
 
template <typename T>
void solve(vector<T>& numbers, const T x) {
	auto sorted = numbers;

	sort(sorted.begin(), sorted.end());

	for (size_t i = 0; i < sorted.size(); i++) {
		T left_over = x - sorted[i];

		auto candidate = lower_bound(sorted.begin() + i + 1, sorted.end(), left_over);

		if (candidate < sorted.end()) {
			if (*candidate == left_over) {
				auto start = find(numbers.begin(), numbers.end(), sorted[i]) - numbers.begin();
				auto end = find(numbers.begin(), numbers.end(), *candidate) - numbers.begin();

				if (end==start) {
					end = find(numbers.begin() + start + 1, numbers.end(), *candidate) - numbers.begin();
				}

				PrintOut(start+1, " ");
				PrintOut(end+1);

				return;
			}
		}
	}

	PrintOut("IMPOSSIBLE");	
	
}
 
void run() {
	size_t n;
	big_int64 x;

	READ(n);
	READ(x);
 
	vector<big_int64> numbers(n);
	ReadStream(numbers);
 
	solve(numbers, x);
}
 
int main() {
	desyncio();
 
	try {
		run();
	} catch (const invalid_argument& exception) {
		cerr << exception.what() << "\n";
		return -1;
	}
    
    return 0;
}