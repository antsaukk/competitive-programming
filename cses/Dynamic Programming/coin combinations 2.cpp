/*
Consider a money system consisting of n coins. 
Each coin has a positive integer value. 
Your task is to calculate the number of distinct ordered ways you can produce a money sum x
using the available coins.
 
For example, if the coins are {2,3,5} and the desired sum is 9, there are 3 ways:
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
https://cses.fi/problemset/task/1636/
*/
 
#include <vector>
#include <set>
#include <cmath>
#include <iostream>
 
using namespace std;
using i64 = int64_t;
constexpr int64_t DIV = 1'000'000'007;
 
template<typename T>
void display(T val){
	cout << val << " ";
}
 
template <typename T>
void solve(T n, T x) {
	T coin = 0;
	vector<T> dp(x + 1);
	dp[0] = 1;
 
	for (i64 i = 0; i < n; i++) {
		cin >> coin;
		for (i64 j = 0; j <= x - coin; j++) {
			dp[j + coin] += dp[j];
			dp[j + coin] %= DIV;
		}
	}
 
	display(dp[x]);
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