/*
You have n coins with positive integer values.
What is the smallest sum you cannot create using a subset of the coins?

INPUT:
The first input line has an integer n: the number of coins.

The second line has n integers x1,x2,…,xn: the value of each coin.

OUTPUT:
Print one integer: the smallest coin sum.

CONSTRAINTS:
1 <= n <= 2*10^5
1 <= x_i <= 10^9
RESULT:
https://cses.fi/alon/result/3647981/
*/

#include <iostream>
#include <vector>
#include <algorithm>

#define ui64 uint64_t

using namespace std;

template<typename T>
void display(T val){
        cout << val;
}

template <typename T>
void read(vector<T>& v) {
        for (size_t i = 0; i < v.size(); i++) {
                cin >> v[i]; 
        }
}

template <typename T>
T solve(vector<T>& v){
        T sum = 1;
        for (size_t i = 0; i < v.size(); i++) {
                if (sum < v[i])
                        break;
                else {
                        sum += v[i];
                }
        }
        return sum;
}


// untie std in/out to speed up computation
void desyncio() {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
}

int main() {
        desyncio();
        ui64 n; 
        cin >> n; 

        vector<ui64> v(n);
        read(v);

        sort(v.begin(), v.end());

        display(solve(v));
        return 0;
}