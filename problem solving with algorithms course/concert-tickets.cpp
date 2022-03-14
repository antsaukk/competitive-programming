/*
There are n concert tickets available, each with a certain price. 
Then, m customers arrive, one after another.
Each customer announces the maximum price they are willing to pay for a ticket, 
and after this, they will get a ticket with the nearest possible price such that it does not exceed the maximum price.

INPUT:
The first input line contains integers n and m: the number of tickets and the number of customers.

The next line contains n integers h1,h2,…,hn: the price of each ticket.

The last line contains m integers t1,t2,…,tm: the maximum price for each customer in the order they arrive.

OUTPUT:
Print, for each customer, the price that they will pay for their ticket. 
After this, the ticket cannot be purchased again.

CONSTRAINTS:
1 <= n, m <= 2*10^5
1 <= h_i, t_i <= 10^9
RESULT:
https://cses.fi/alon/result/3674068/
*/

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

#define ui64 uint64_t

using namespace std;

template<typename T>
void display(T val) {
        cout << val << "\n";
}

template<typename T>
void read(multiset<T>& prices, size_t n) {
        for (size_t i = 0; i < n; i++){
                T p;
                cin >> p;
                prices.insert(p);
        }
}

template <typename T>
void solve(multiset<T>& prices, size_t m){
        for(size_t i = 0; i < m; i++){
                T offer;
                cin >> offer;
                auto element = prices.upper_bound(offer);
                if (element != prices.begin()){
                        display(*(--element));
                        prices.erase(element);
                }
                else
                        display(-1);
        }
}

// untie std in/out to speed up computation
void desyncio() {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
}

int main() {
        desyncio();
        size_t n, m; 
        cin >> n >> m;

        multiset<ui64> prices;
        read(prices, n);

        solve(prices, m);
        return 0;
}