/*
Consider a money system consisting of n coins. 
Each coin has a positive integer value. 
Your task is to produce a sum of money x using the available coins in such a way that the number of coins is minimal.

For example, if the coins are {1,5,7} and the desired sum is 11, an optimal solution is 5+5+1 which requires 3 coins.
 
INPUT:
The first input line has two integers n and x: the number of coins and the desired sum of money.
 
The second line has n distinct integers c1,c2,…,cn: the value of each coin.
 
OUPUT:
Print one integer: the minimum number of coins. If it is not possible to produce the desired sum, print −1.
 
CONSTRAINTS:
1 <= n  <= 100
1 <= x  <= 10^6
1 <= ci <= 10^6
 
VERIFY:
 
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
inline void read(vector<T>& container) {
	for (int i = 0; i < container.size(); i++)
		cin >> container[i];
}
 
inline void desyncio() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
}
 
template <typename T>
void solve(T n, T x) {
	vector<T> coins(n);
	read(coins);
 
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
 
int main() {
	desyncio();
 
	i64 n, x;
	cin >> n >> x;
 
	solve(n, x);
 
	return 0;
}