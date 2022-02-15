/*
Consider an algorithm that takes as input a positive integer n.
If n is even, the algorithm divides it by two, and if n is odd,
the algorithm multiplies it by three and adds one.
The algorithm repeats this, until n is one.

The task is to simulate the execution of the algorithm for a given value of n.

INPUT:
The only input line contains an integer n.

OUTPUT:
Print a line that contains all values of n during the algorithm.

CONSTRAINTS:
1 <= n <= 10^6

RESULT:
https://cses.fi/alon/result/3509611/
*/

#include <iostream>
#define i64 int64_t

using namespace std;

void display(i64 n){
        cout << n << " ";
}

void solve(i64 n){
        while(n!=1){
                if(n%2){
                        n *= 3;
                        n += 1;
                        display(n);
                } else {
                        n /= 2;
                        display(n);
                }
        }
}

int main() {
        i64 n;
        cin >> n;
        display(n);
        solve(n);
        return 0;
}
