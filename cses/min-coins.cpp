/*
Consider a money system consisting of n
coins. Each coin has a positive integer value. 
Your task is to calculate the number of distinct ordered ways you can produce a money sum x
using the available coins.
 
 
For example, if the coins are {2,3,5}
and the desired sum is 9, there are 3 ways:
2+2+5
3+3+3
2+2+2+3
 
INPUT:
The first input line has two integers n and x: the number of coins and the desired sum of money.
 
The second line has n distinct integers c1,c2,…,cn: the value of each coin.
 
OUPUT:
Print the number of ways modulo 10^9+7.
 
CONSTRAINTS:
1 <= n  <= 100
1 <= x  <= 10^6
1 <= ci <= 10^6
 
VERIFY:
https://cses.fi/problemset/task/1634/
*/
 
#include <vector>
#include <cmath>
#include <limits.h>
#include <iostream>
 
using namespace std;
using i64 = int64_t;
 
template<typename T>
void display(T val){
	cout << val << " ";
}
 
template <typename T>
void solve(T n, T x) {
	vector<T> coins(n);
 
	for (int i = 0; i < n; i++) 
		cin >> coins[i];
 
	vector<T> dp(x + 1);
	dp[0] = 0;
 
	T INF = numeric_limits<T>::max() - 1;
 	
	for (i64 i = 1; i <= x; i++) {
		dp[i] = INF;
		for (auto c : coins) {
			if (i - c >= 0) {
				dp[i] = min(dp[i], dp[i-c] + 1);
			}
		}
	}
 
	display(dp[x] < INF ? dp[x] : -1);
}
 
 
inline void desyncio() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
}
 
int main() {
	desyncio();
 
	i64 n, x;
	cin >> n >> x;
 
	solve(n, x);
 
	return 0;
}