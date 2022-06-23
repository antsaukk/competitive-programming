#include <vector>
#include <cmath>
#include <iostream>
 
/*
Aliases
*/
using namespace std;
using i64 = int64_t;
 
/*
Utilities
*/
template<typename T>
inline void display(T val){
	cout << val << " ";
}
 
inline void desyncio() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
}
 
/*
You are given an integer n. On each step, you may subtract one of the digits from the number.
 
How many steps are required to make the number equal to 0?
 
INPUT:
The only input line has an integer n.
 
OUPUT:
Print one integer: the minimum number of steps.
 
CONSTRAINTS:
1 <= n <= 10^6
 
SOLUTION: 
Dynamic programming
 
VERIFY:
https://cses.fi/problemset/result/4087732/
*/
 
 
/*
Structure, which does house-keeping operations of data structures
 
needed to mainatain construction of dynamic programming solution
*/
template <typename T>
struct DPtable {
	explicit DPtable(T n) : 
	dp(n),
	ready(n)
	{}
 
	void SetDP(T value, T index) {
		dp[index] = value;
	}
 
	void SetReady(T index) {
		ready[index] = 1;
	}
 
	const T DP(T index) const {
		return dp[index];
	}
 
	const T Ready(T index) const {
		return ready[index];
	}
 
private:
	vector<T> dp;
	vector<T> ready;
};
 
 
/*
Get single digits from an integer and store them in the vector as single values.
 
This way is efficient since array digits may contain max 6 values.
*/
template <typename T>
void digitify(vector<T>& digits, T n) {
	T x = n;
	while(x >= 10) {
		digits.push_back(x % 10);
		x /= 10;
	}
	digits.push_back(x);
}
 
/*
Dynamic programming algorithm to solve the problem described above: 
 
Iterate over all digits in the number and recurse down to the new number by substracting the digit
 
which gives smallest number of steps to reach zero. Maintain partial solutions in dp table and look up
 
if the solution has already been computed.
*/
template <typename T>
T solve(DPtable<T>& checker, T n) {
	if (n <= 0) return 0;
	if (checker.Ready(n)) return checker.DP(n);
 
	vector<T> digits;
	digitify(digits, n);
	
 
	T best = numeric_limits<T>::max() - 1;
 
	for (auto dg : digits) 
		best =  dg > 0 ? min(best, solve(checker, n - dg) + 1) : best;
 
	checker.SetDP(best, n);
	checker.SetReady(n);
 
	return best;
}
 
int main() {
	desyncio();
 
	i64 n;
	cin >> n;
 
	DPtable<i64> r(n+1);
 
	display(solve(r, n));
 
	return 0;
}
