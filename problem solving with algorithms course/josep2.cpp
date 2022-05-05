/*
Consider a game where there are n children (numbered 1,2,…,n) in a circle.
During the game, repeatedly k children are skipped and one child is removed from the circle. 
In which order will the children be removed?

INPUT:
The only input line has an integer n and k.

OUTPUT:
Print n integers: the removal order.

CONSTRAINTS:
1 <= n <= 2*10^5
0 <= k <= 10^9
RESULT:

*/

#include <iostream>
#include <vector>
#include <queue>
#include <numeric>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define ui64 uint64_t

typedef tree<size_t,null_type,less<size_t>,rb_tree_tag,tree_order_statistics_node_update> indexed_set;

template<typename T>
void display(T val) {
        cout << val << " ";
}

enum class State {
        Empty,
        Naive,
        V1,
        V2
};


// better do via inheritance -- continue
template <typename T,
          typename K>
class JosephusCalculator {
public:
        explicit JosephusCalculator(size_t n,
                                    ui64 k) :
        n_(n),
        run_(n),
        index_(0u),
        k_(k),
        counter_(1u),
        step(-1),
        range_(n)
        {
                iota(range_.begin(), range_.end(), 1);
                init_index_set_();
        }

        void init_index_set_() {
                for (const auto el : range_) {
                        Jcollection_.insert(el);
                }
        }

        void increase_counter_()        { counter_++; }

        void reset_counter_()           { counter_ = 1; }

        void decrease_iterations_()     { run_--; }

        void remove_element_()          { range_[index_] = 0; }

        void index_up_()                { index_++; index_ %= n_; }

        void solve_naive_();

        void solve_efficient_v1_();

        void solve_efficient_v2_();

        void empty_collection_();

private:
        T n_            = 0; // common
        T run_          = 0; // common
        T index_        = 0; // common
        K k_            = 0; // common

        T counter_      = 0; //naive

        int64_t step    = -1; //v1

        vector<T> range_; //naive
        indexed_set Jcollection_; //v1

        queue<T> removal_waiting_elements_; //v1
};

template <typename T, typename K>
void JosephusCalculator<T,K>::
        solve_naive_(){

        while (run_) {
                if (range_[index_]) {
                        if (counter_ % (k_+1) != 0) {
                                increase_counter_();
                        } else {
                                display(range_[index_]);
                                decrease_iterations_();
                                remove_element_();
                                reset_counter_();
                        }
                }
                index_up_();
        }
}

template <typename T, typename K>
void JosephusCalculator<T,K>::
        solve_efficient_v1_(){
        T current_index = index_;

        while(run_) {

                if (step == -1) {
                        current_index += k_;
                } else {
                        current_index = step;
                        step          = -1;
                }
                
                if (current_index < n_) {
                        auto element  = Jcollection_.find_by_order(current_index);
                        removal_waiting_elements_.push(*element);
                        display(*element);
                        decrease_iterations_();
                        current_index++;
                } else {
                        step          = current_index - n_;
                        empty_collection_();
                        n_            = Jcollection_.size();
                } 
        }
}

template <typename T, typename K>
void JosephusCalculator<T,K>::
        empty_collection_(){

        while(!removal_waiting_elements_.empty()) {
                T element_to_be_removed = removal_waiting_elements_.front();
                removal_waiting_elements_.pop();
                Jcollection_.erase(element_to_be_removed);
        }
}

// untie std in/out to speed up computation
void desyncio() {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
}

int main() {
        desyncio();
        size_t n;
        ui64 k; 
        cin >> n >> k;

        JosephusCalculator<size_t, ui64> jc(n, k);
        jc.solve_efficient_v1_();

        return 0;
}
