/*
You are given an array of n integers. You want to modify the array so that it is increasing, i.e.,
every element is at least as large as the previous element.

On each move, you may increase the value of any element by one.
What is the minimum number of moves required?

INPUT:
The first input line contains an integer n: the size of the array.

Then, the second line contains n integers x1,x2,…,xn: the contents of the array.

OUTPUT:
Print the minimum number of moves.

CONSTRAINTS:
1 <= n <= 2*10^5
1 <= x_i <= 10^9

RESULT:
https://cses.fi/alon/result/3511538/
*/

#include <iostream>
#include <vector>

#define i64 int64_t

using namespace std;

void read(vector<i64>& v) {
        for(size_t i = 0; i < v.size(); i++)
                cin >> v[i];
}

void display(size_t n){
        cout << n << " ";
}

size_t solve(vector<i64>& v){
        i64 result = 0;
        for(size_t i = 1; i < v.size(); i++) {
                if (v[i] - v[i-1] < 0){
                        auto increment = v[i-1] - v[i];
                        result += increment;
                        v[i] += increment;
                }
        }
        return result;
}

int main() {
        size_t n;
        cin >> n;

        vector<i64> v(n);
        read(v);

        display(solve(v));
        return 0;
}
