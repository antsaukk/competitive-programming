/*
Given an array of n integers, your task is to calculate the number of subarrays that have at most k distinct values.

INPUT:
The first input line has two integers n and k.

The next line has n integers x1,x2,…,xn: the contents of the array.
OUTPUT:
Print one integer: the number of subarrays.
CONSTRAINTS:
1 <= k, n <= 2*10^5
1 <= x_i <= 10^9
RESULT:

*/

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

#define ui64 uint64_t

using namespace std;

ui64 subarrays = 0;

template<typename T>
void display(T val) {
        cout << val << " ";
}

template <typename Container,
          typename T>
void read(Container& container, T size_)
{
        for(size_t i = 0; i < size_; i++) {
                ui64 element;
                cin >> element;
                container.insert(container.end(),
                                 forward<ui64>(element));
                display("there");
        }
}

template <typename T,
          typename K>
bool there_is_space_in_a_bucket(set<T>& bucket,
                                K limit)
{
        return bucket.size() < limit;
}

void increase_subarrays() 
{
        subarrays++;
}

template <typename Container,
          typename T>
void solve(Container& container,
           T range)
{
        for(auto left = container.begin();
                left < container.end(); 
                next(left)) {
                set<ui64> bucket;
                auto right = left;
                while(there_is_space_in_a_bucket(bucket, range) 
                        && right < container.end())
                {
                        bucket.insert(*right);
                        next(right);
                }
                increase_subarrays();
        }
}


// untie std in/out to speed up computation
void desyncio() {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
}

int main() {
        //desyncio();

        size_t n, k; 
        cin >> n >> k;

        vector<ui64> v(n);
        read(v, n);
        display("here");
        solve(v, k);

        display(subarrays);

        return 0;
}