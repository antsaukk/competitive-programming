/*
Consider a game where there are n children (numbered 1,2,…,n) in a circle.
During the game, every second child is removed from the circle, until there are no children left. 
In which order will the children be removed?

INPUT:
The only input line has an integer n.

OUTPUT:
Print n integers: the removal order.

CONSTRAINTS:
1 <= n <= 2*10^5
RESULT:
https://cses.fi/alon/result/3648613/
*/

#include <iostream>
#include <vector>
#include <numeric>

#define ui64 uint64_t

using namespace std;

template<typename T>
void display(T val) {
        cout << val << " ";
}

template <typename T>
void solve(vector<T>& v, T n){
        size_t counter = 1;
        size_t run = n;
        size_t i = 0;

        while (run) {
                if (v[i]) {
                        if (counter % 2) counter++;
                        else {
                                display(v[i]);
                                counter++;
                                run--;
                                v[i] = 0;   
                        }
                }

                i++;
                i %= n;
        }
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

        vector<size_t> v(n); 
        iota(v.begin(), v.end(), 1);

        solve(v, n);
        return 0;
}