/*
There is a list of n numbers and two players who move alternately.
On each move, a player removes either the first or last number from the list,
and their score increases by that number.Both players try to maximize their scores.
 
What is the maximum possible score for the first player when both players play optimally?
 
INPUT:
The first input line contains an integer n: the size of the list.
The next line has n integers x1,x2,…,xn: the contents of the list.
 
OUTPUT:
Print the maximum possible score for the first player.
 
CONSTRAINTS:
1 <= n <= 5000
−10^9<=xi<=10^9
 
RESULT:
https://cses.fi/alon/result/4051682/
*/
 
#include <vector>
#include <iostream>
#include <cmath>
 
#define BigInt int64_t
constexpr size_t indent = 2;
 
using namespace std;
 
template <typename T>
inline void display(T value) {
    cout << value;
}
 
template <typename T>
struct DPsolver {
    explicit DPsolver(size_t n) :
    n_(n),
    dp_(n, vector<T>(n, -1)),
    range_(n) 
    {
        read();
    }
 
    inline void read() {
        for (size_t i = 0; i < size(); i++)
            cin >> range_[i];
    }
 
    inline T unpack(int index_i, int index_j) {
        return dp_[index_i][index_j];
    }
 
    inline void pack(T value, int index_i, int index_j) {
        dp_[index_i][index_j] = value;
    }
 
    inline T sequence_value(int index) {
        return range_[index];
    }
 
    inline const size_t size() const {
        return n_ - indent;
    }
 
private:
    size_t n_;
    vector<vector<T>> dp_;
    vector<T> range_;
};
 
template <typename T>
T solve(DPsolver<T>& solver,
    int left,
    int right) {
    if (left > right) return 0;
    if (solver.unpack(left, right) != -1)
        return solver.unpack(left, right);
 
    T value_left  = solver.sequence_value(left) + 
                    min(solve(solver, left+2, right),
                        solve(solver, left+1, right-1));
 
    T value_right = solver.sequence_value(right) +
                    min(solve(solver, left+1, right-1),
                        solve(solver, left, right-2));
 
    solver.pack(max(value_left, value_right),
                left,
                right);
    return solver.unpack(left, right);
}
 
int main() {
    size_t n;
    cin >> n;
 
    DPsolver<BigInt> v(n + indent);
 
    display(solve(v, 0, n-1));
 
    return 0;
}