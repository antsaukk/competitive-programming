/*
You are given an array containing n integers.
Your task is to determine the longest increasing subsequence in the array, i.e.,
the longest subsequence where every element is larger than the previous one.

A subsequence is a sequence that can be derived from the array by deleting some elements without changing the order of the remaining elements.

INPUT:
The first line contains an integer n: the size of the array.
After this there are n integers x1,x2,…,xn: the contents of the array.

OUPUT:
Print the length of the longest increasing subsequence.

CONSTRAINTS:
1 <= n <= 2*10^5
1 <= xi <= 10^9
*/

#include <vector>
#include <algorithm>
#include <iostream>
 
using namespace std;
using ui64 = uint64_t; 
 
template<typename T>
void display(T val){
	cout << val << " ";
}
 
template <typename T>
inline void read(vector<T>& container) {
	for (size_t i = 0; i < container.size(); i++)
		cin >> container[i];
}
 
template <typename T>
void solve(vector<T>& container) {
 	vector<T> sequence;

	for (size_t i = 0; i < container.size(); i++) {
		auto bound = lower_bound(sequence.begin(), sequence.end(), container[i]);
		if (bound == sequence.end()) {
			sequence.push_back(container[i]);
		} else {
			*bound = container[i];
		}
	}
	display(sequence.size());
}
 
inline void desyncio() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
}
 
int main() {
	desyncio();
 
	size_t n;
	cin >> n;
 
	vector<ui64> v(n); 
	read(v); 
 
	solve(v); 
 
 
	return 0;
}