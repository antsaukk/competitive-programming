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
#include <map>
#include <algorithm>

#define ui64 uint64_t
 
using namespace std;

ui64 subarrays = 0;
 
template<typename T>
void display(T val) {
        cout << val;
}
 
/*template <typename Container,
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
}*/
 
template <typename T>
void read(vector<T>& container, size_t size_)
{
        for(size_t i = 0; i < size_; i++) {
                ui64 element;
                cin >> element;
                container[i] = element;
        }
}
 
template <typename T,
          typename K>
bool there_is_space_in_a_bucket(map<T,K>& bucket,
                                K limit)
{
        return bucket.size() <= limit;
}
 
void increase_number_of_subarrays(size_t s) 
{
        subarrays+=s;
}
 
/*template <typename Container,
          typename T>
void solve(Container& container,
           T range)
{
        typedef typename Container::iterator iter;
        for(iter left = container.begin();
                left != container.end(); 
                ++left) {
                set<ui64> bucket;
                iter right = left;
                display("here");
                while(there_is_space_in_a_bucket(bucket, range) 
                        && right != container.end())
                {
                        bucket.insert(*right);
                        next(right);
                }
                increase_number_of_subarrays();
        }
}*/

size_t upper_bound(size_t left, size_t range, size_t size_) {
        return left + range < size_ ? left + range : size_;
}
 
template <typename T>
void solve(vector<T>& container,
                size_t size_,
                size_t range)
{
        // compute upper the least bound for subarray
        // starting at 0
        size_t right = upper_bound(0u, range, size_);

        // to count frequency of values in subarrays
        map<T,size_t> bucket;

        // add values of subarray from [0, right)
        for(size_t left = 0; left < right; left++) {
                bucket[container[left]]++;
        }

        for(size_t left = 0; left < size_; left++) {
                right = upper_bound(left, range, size_);
                
                // at index left there ar eat least right-left subarrays
                increase_number_of_subarrays(right-left);

                // shifting least upperbound by 1
                // check how many subarrays can still be formed
                for (size_t counter = right; counter < size_; counter++) {
                        bucket[container[counter]]++;

                        // increase amount of subarrays if there is
                        // still space in a bucket or finish
                        if (there_is_space_in_a_bucket(bucket, range)) {
                                increase_number_of_subarrays(1u); //
                        } else {
                                right = counter;
                                break;
                        }
                }
                
                // if bucket has "overflowed": 
                // check whether you can delete the left most element
                // or the right most element
                if (right < size_) {
                        if (bucket.at(container[left]) == 1) {
                                bucket.erase(container[left]);
                        } else{
                                bucket.erase(container[right]);
                                bucket[container[left]]--;
                        }

                } else {
                        bucket[container[left]]--;
                }
                

        }
}
 
 
// untie std in/out to speed up computation
void desyncio() {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
}
 
int main() {
        desyncio();
 
        size_t n, k; 
        cin >> n >> k;
 
        vector<ui64> v(n);
        read(v, n);
        solve(v, n, k);
 
        display(subarrays);
 
        return 0;
}