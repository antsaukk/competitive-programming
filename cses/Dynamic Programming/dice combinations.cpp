/*
Your task is to count the number of ways to construct sum n by throwing a dice one or more times.
Each throw produces an outcome between 1 and 6.
 
For example, if n=3, there are 4 ways:
1+1+1
1+2
2+1
3
 
INPUT:
The only input line has an integer n.
 
OUPUT:
Print the number of ways modulo 10^9+7.
 
CONSTRAINTS:
1 <= n <= 10^6
 
VERIFY:
https://cses.fi/problemset/result/4074240/
*/
 
#include <vector>
#include <cmath>
#include <iostream>
 
using namespace std;
using i64 = int64_t;
constexpr long long DIV = 1'000'000'007;
 
template<typename T>
void display(T val){
	cout << val << " ";
}
 
template <typename T>
void solve(T n) {
	vector<int> dices = {1, 2, 3, 4, 5, 6};
	vector<T> dp(n + 1);
	dp[0] = 1;
 
	for (i64 i = 1; i <= n; i++) {
		for (auto dice : dices) {
			if (i - dice >= 0) {
				dp[i] += dp[i-dice];
				dp[i] %= DIV;
			}
		}
	}
	display(dp[n]);
}
 
 
inline void desyncio() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
}
 
int main() {
	desyncio();
 
	i64 n;
	cin >> n;
 
	solve(n);
 
	return 0;
}