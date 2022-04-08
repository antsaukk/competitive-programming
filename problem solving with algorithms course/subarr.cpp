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
        right_pointer_(0),
        container_(n)
        {
                read();
        }

        void read() 
        {
                for(size_t i = 0; i < size_(); i++)
                        cin >> container_[i]; 
        }

        bool there_is_space_in_a_bucket()
        {
                return bucket_sz() <= range_();
        }

        void increase_number_of_subarrays(K s) 
        {
                subarrays_ += s;
        }

        K lower_bound(K start) 
        {
                return start + range_() < size_() ? start + range_() : size_();
        }

        void init_bucket()
        {
                set_right_pointer(lower_bound(0u));
                for(size_t left = 0; left < right_pointer_; left++)
                        bucket_[container_[left]]++;
        }

        void solve() 
        {
               // compute upper the least bound for subarray
                // starting at 0
                //size_t right = lower_bound(0u);

                // add values of subarray from [0, right)
                init_bucket();

                for(size_t left = 0; left < size_(); left++) {
                        //right = lower_bound(left);
                        set_right_pointer(lower_bound(left));
                        
                        // at index left there ar eat least right-left subarrays
                        // if right < size_
                        increase_number_of_subarrays(right_pointer_-left);

                        // shifting least lowerbound by 1
                        // check how many subarrays can still be formed
                        while(right_pointer_ < size_() && there_is_space_in_a_bucket()) {
                                if (right_pointer_ >= get_bound_())
                                        bucket_[container_[right_pointer_]]++;
                                if (there_is_space_in_a_bucket()) {
                                        increase_number_of_subarrays(1u);
                                        right_pointer_++;
                                }
                        }

                        set_bound(max(right_pointer_, get_bound_()));
                        
                        // if bucket_ has "overflowed": 
                        // check whether you can delete the leftmost element
                        // or the rightmost element from the range_() 
                        // starting at left
                        if (!there_is_space_in_a_bucket()) {
                                try {
                                        if (bucket_.at(container_[left])==1){
                                                bucket_.erase(container_[left]);
                                                bound_++;
                                        }
                                        else {
                                                bucket_[container_[left]]--;
                                                bucket_.erase(container_[right_pointer_]);
                                        }   
                                } catch (const std::exception& e) {
                                        display(e.what());
                                }
                                
                        } else if (there_is_space_in_a_bucket() && right_pointer_ == size_()) {
                                try {
                                        if (bucket_.at(container_[left])==1)
                                                bucket_.erase(container_[left]);
                                        else {
                                                bucket_[container_[left]]--;
                                                
                                        }
                                } catch (const std::exception& e) {
                                        display(e.what());
                                }
                                
                        }
                }
        }

        const void show()              const { display(number_of_subarrays_()); }

        void set_right_pointer(K r)          { right_pointer_ = r; }

        void set_bound(K b)                  { bound_ = b; }

        const K get_bound_()           const { return bound_; }

        const K size_()                const { return n_; }

        const K range_()               const { return k_; }

        const K number_of_subarrays_() const { return subarrays_; }

        const size_t bucket_sz()       const { return bucket_.size(); }

private:
       K n_                 = 0;
       K k_                 = 0;
       K subarrays_         = 0;
       K bound_             = 0;
       K right_pointer_     = 0;
       vector<T> container_;
       map<T,K> bucket_;
       
};
 
template <typename T>
void read(vector<T>& container, const size_t size_)
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

size_t lower_bound(size_t left, size_t range, size_t size_) {
        return left + range < size_ ? left + range : size_;
}
 
template <typename T>
void solve(const vector<T>& container,
                const size_t size_,
                const size_t range)
{
        // compute upper the least bound for subarray
        // starting at 0
        size_t right = lower_bound(0u, range, size_);

        // to count frequency of values in subarrays
        map<T,size_t> bucket;

        // add values of subarray from [0, right)
        for(size_t left = 0; left < right; left++) {
                bucket[container[left]]++;
        }

        size_t bound = 0;

        for(size_t left = 0; left < size_; left++) {
                right = lower_bound(left, range, size_);
                
                // at index left there ar eat least right-left subarrays
                // if right < size_
                increase_number_of_subarrays(right-left);

                // shifting least lowerbound by 1
                // check how many subarrays can still be formed
                while(right < size_ && there_is_space_in_a_bucket(bucket, range)) {
                        if (right >= bound)
                                bucket[container[right]]++;
                        if (there_is_space_in_a_bucket(bucket, range)) {
                                increase_number_of_subarrays(1u);
                                right++;
                        }
                }

                bound = max(right, bound);
                
                // if bucket has "overflowed": 
                // check whether you can delete the leftmost element
                // or the rightmost element from the range 
                // starting at left
                if (!there_is_space_in_a_bucket(bucket, range)) {
                        try {
                                if (bucket.at(container[left])==1){
                                        bucket.erase(container[left]);
                                        bound++;
                                }
                                else {
                                        bucket[container[left]]--;
                                        bucket.erase(container[right]);
                                }   
                        } catch (const std::exception& e) {
                                display(e.what());
                        }
                        
                } else if (there_is_space_in_a_bucket(bucket, range) && right == size_) {
                        try {
                                if (bucket.at(container[left])==1)
                                        bucket.erase(container[left]);
                                else {
                                        bucket[container[left]]--;
                                        
                                }
                        } catch (const std::exception& e) {
                                display(e.what());
                        }
                        
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

        UniqueSubarrays<ui64, size_t> subarr(n, k);
        subarr.solve();
        subarr.show();
        /*vector<ui64> v(n);
        read(v, n);
        solve(v, n, k);*/
 
        //display(subarrays);
 
        return 0;
}