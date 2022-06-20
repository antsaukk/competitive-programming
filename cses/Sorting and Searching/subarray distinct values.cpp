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
https://cses.fi/alon/result/3806538/
*/

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

#define ui64 uint64_t
 
using namespace std;

// generic print to stdout
template<typename T>
void display(T val) {
        cout << val;
}

// untie std in/out to speed up computation
void desyncio() {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
}

template<typename T,
         typename K>
class UniqueSubarrays {
public:
        explicit UniqueSubarrays(size_t n,
                                 size_t k) :
        n_(n),
        k_(k),
        subarrays_(0),
        bound_(0),
        right_(0),
        container_(n)
        {
                read();
        }

        void read() 
        {
                for(size_t i = 0; i < size_(); i++)
                        cin >> container_[i]; 
        }

        void init_bucket()
        {
                set_right_pointer(lower_bound(0u));
                for(size_t left = 0; left < right_pointer_(); left++)
                        increase_element_in_bucket(left);
        }

        K lower_bound(K start)                  { return start + range_() < size_() ? start + range_() : size_(); }

        bool there_is_space_in_a_bucket()       { return bucket_sz() <= range_();}

        void increase_number_of_subarrays(K s)  { subarrays_ += s; }

        void remove_from_bucket(T element)      { bucket_.erase(element); }

        void decrease_element_in_bucket(K index) { bucket_[container_[index]]--; }

        void increase_element_in_bucket(K index) { bucket_[container_[index]]++; }

        void set_right_pointer(K r)             { right_ = r; }

        void set_bound(K b)                     { bound_ = b; }

        const void show()                 const { display(number_of_subarrays_()); }

        const K right_pointer_()          const { return right_; }

        const K right_bound_()            const { return bound_; }

        const K size_()                   const { return n_; }

        const K range_()                  const { return k_; }

        const K number_of_subarrays_()    const { return subarrays_; }

        const size_t bucket_sz()          const { return bucket_.size(); }

        void shift_right_pointer(); 
        
        void shift_left_pointer(K left);

        void solve();

private:
       K n_                 = 0;
       K k_                 = 0;
       K subarrays_         = 0;
       K bound_             = 0;
       K right_             = 0;
       vector<T> container_;
       map<T,K> bucket_;
       
};


/*
At every index in array compute the maximum number 
of arrays that have at most k_ distinct elements
the sum of results for every index is the maximum
amount of subarrays. 
Solved with two pointers method in O(nlogn),
where log comes from red-black tree searching,
insertion and removal.
*/
template <typename T,
          typename K>
void UniqueSubarrays<T,K>::solve()
{
        // add values of subarray from [0, right)
        init_bucket();

        for(size_t left = 0; left < size_(); left++) 
        {
                // define minimum number of subarrays 
                // starting from index left
                // be default it is at least "right-left"
                // if "right < size_"
                set_right_pointer(lower_bound(left));
                
                // add up to result
                increase_number_of_subarrays(right_pointer_() - left);

                // if right pointer is not at the end of array
                // and there is space in the bucket
                // check how many subarrays can still be formed
                // starting from index "right_pointer_"
                shift_right_pointer();
                        
                // if bucket_ has overflowed: 
                // check whether you can delete the leftmost element
                // or the rightmost element from the range "right_pointer_ - left"
                // starting at "left"
                shift_left_pointer(left);
        }
}

template <typename T,
          typename K>
void UniqueSubarrays<T,K>::shift_left_pointer(K left)
{
        if (!there_is_space_in_a_bucket()) {
                // catching exception if bucket.at(container[left])
                // does not exists
                try {
                        if (bucket_.at(container_[left]) == 1){
                                remove_from_bucket(container_[left]);
                                set_bound(right_bound_() + 1);
                        }
                        else {
                                decrease_element_in_bucket(left);
                                remove_from_bucket(container_[right_pointer_()]);
                        }   
                } catch (const exception& e) {
                        display(e.what());
                }     
                } else if (right_pointer_() == size_()) {
                // catching exception if bucket.at(container[left])
                // does not exists
                try {
                        if (bucket_.at(container_[left]) == 1)
                                remove_from_bucket(container_[left]);
                        else
                                decrease_element_in_bucket(left);
                } catch (const exception& e) {
                        display(e.what());
                }  
        }        
}

template <typename T,
          typename K>
void UniqueSubarrays<T,K>::shift_right_pointer()
{
        while(right_pointer_() < size_() && 
                there_is_space_in_a_bucket()) {

                if (right_pointer_() >= right_bound_())
                        increase_element_in_bucket(right_pointer_());

                if (there_is_space_in_a_bucket()) {
                        increase_number_of_subarrays(1u);
                        set_right_pointer(right_pointer_() + 1);
                }
        }

        // check the bound to verify that frequencies of 
        // elements in the map might increase
        set_bound(max(right_pointer_(), right_bound_()));
}
 
int main() {
        desyncio();
 
        size_t n, k; 
        cin >> n >> k;

        UniqueSubarrays<ui64, size_t> subarr(n, k);
        subarr.solve();
        subarr.show();
 
        return 0;
}