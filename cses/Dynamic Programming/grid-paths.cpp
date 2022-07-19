#include <vector>
#include <cmath>
#include <iostream>

/*
Aliases
*/
using namespace std;
using i64 = int64_t;
constexpr long long DIV = 1'000'000'007;

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
Consider an n x n grid whose squares may have traps.
It is not allowed to move to a square with a trap.

Your task is to calculate the number of paths from the upper-left square to the lower-right square.
You can only move right or down.

INPUT:
The first input line has an integer n: the size of the grid.
After this, there are n lines that describe the grid.
Each line has n characters: . denotes an empty cell, and * denotes a trap.


OUPUT:
Print the number of paths modulo 10^9+7.

CONSTRAINTS:
1 <= n <= 1000

SOLUTION:
Dynamic programming

VERIFY:
https://cses.fi/problemset/result/4087732/
*/

/*
Structure, which handles house keeping of map
and dynamic programming grid
*/
template <typename T>
struct DPtable {
	explicit DPtable(T n) :
	N(n),
	map(n, vector<T>(n)),
	dp(n,  vector<T>(n))
	{}

	inline void Read() {
		for (int i = 1; i <= MapSize(); i++) {
			for (int j = 1; j <= MapSize(); j++) {
				char c;
				cin >> c;

				SetMap(i, j, c == '.' ? 0 : -1);
			}
		}
	}

	inline void SetDP(T y, T x, T value) {
		dp[y][x] = value;
	}

	inline void SetMap(T y, T x, T value) {
		map[y][x] = value;
	}

	inline const T DP(T y, T x) const {
		return dp[y][x];
	}

	inline const T LocationAt(T y, T x) const {
		return map[y][x];
	}

	inline const size_t IsNotWall(T y, T x) const {
		return LocationAt(y, x) != -1;
	}

	inline const T MapSize() const {
		return N - 1;
	}

private:
	T N;
	vector<vector<T>> map;
	vector<vector<T>> dp;
};

/*
Dynamic programming algorithm to solve the problem described above:

Let DP(y, x) = DP(y, x) + DP(y-1, x) + DP(y, x-1) be number of paths
leading to the cell at the location (y, x) on the map. Then, DP(n, n)
contains total number of paths starting at upper left corner and ending
at lower right corner. Iterate through the map and maintain DP table
according to recursive formula above. Works in O(n²)
*/
template <typename T>
void solve(DPtable<T>& Grid) {
	if (!Grid.IsNotWall(1, 1)) return;

	Grid.SetDP(1, 1, 1);

	for (int i = 1; i <= Grid.MapSize(); i++) {
		for (int j = 1; j <= Grid.MapSize(); j++) {
			if (Grid.IsNotWall(i, j)) {
				T ways = Grid.DP(i, j) +
						 Grid.DP(i-1, j) +
						 Grid.DP(i, j-1);

				Grid.SetDP(i, j, ways % DIV);
			}
		}
	}
}

void run() {
	desyncio();

	int n;
	cin >> n;

	DPtable<int> Grid(n+1);
	Grid.Read();

	solve(Grid);

	display(Grid.DP(n, n));
}

int main() {
	run();
	return 0;
}
