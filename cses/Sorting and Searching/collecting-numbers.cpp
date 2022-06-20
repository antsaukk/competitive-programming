/*
You are given an array that contains each number between 1…n exactly once. 
Your task is to collect the numbers from 1 to n in increasing order.

On each round, you go through the array from left to right and collect 
as many numbers as possible. What will be the total number of rounds?

INPUT:
The first line has an integer n: the array size.

The next line has n integers x1,x2,…,xn: the numbers in the array.

OUTPUT:
Print one integer: the number of rounds.

CONSTRAINTS:
1 <= n <= 2*10^5
RESULT:
https://cses.fi/alon/result/3643041/
*/

#include <iostream>
#include <vector>

#define ui64 uint64_t

using namespace std;

template<typename T>
void display(T val){
        cout << val;
}

template<typename T>
T solve(vector<T>& v, T n){
        T count = 0;
        T num;
        for (size_t i = 0; i < n; i++) {
                cin >> num;
                if (v[num] == 0) 
                        count++;
                if (num < n)
                        v[num + 1] = 1;

        }
        return count;
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

        vector<ui64> v(n + 1);

        display(solve(v, n));
        return 0;
}