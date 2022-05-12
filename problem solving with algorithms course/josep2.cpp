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

//#include "profile.h"

using namespace std;
using namespace __gnu_pbds;

#define ui64 uint64_t

typedef tree<size_t, null_type,less<size_t>, rb_tree_tag, tree_order_statistics_node_update> indexed_set;

template<typename T>
void display(T val) {
        cout << val << " ";
}

template <typename T, typename K> 
class JosephusCalculator {
public:
        JosephusCalculator(size_t n, ui64 k) : 
        n_(n),
        run_(n),
        index_(0u),
        k_(k)
        {}

        virtual void init() = 0;

        virtual void solve() = 0;

        void increase_index()       { index_++; }

        void modulate_index()       { index_ %= n_; }

        void decrease_iterations_() { run_--; }

        void setSize(T value)       { n_ = value; }

        K getOrderStep() const      { return k_; }

        T getIndex() const          { return index_; }

        T getSize()  const          { return n_; }

        T getRun()  const           { return run_; }
private:
        T n_; 
        T run_; 
        T index_;
        K k_;
};

template <typename T, typename K>
class JosephusNaive : public JosephusCalculator<T, K> {
public:
        JosephusNaive(size_t n, ui64 k) :
        JosephusCalculator<T, K> (n, k),
        counter_(1u),
        range_(n)
        {
                init();
        }

        void init() override {
                iota(range_.begin(), range_.end(), 1);
        }

        void increase_counter_()        { counter_++; }

        void reset_counter_()           { counter_ = 1; }

        void remove_element_();       

        void index_up_();              

        void solve() override;

private:
        T counter_ ;

        vector<T> range_; 
};

template<typename T, typename K>
void JosephusNaive<T, K>::remove_element_() {
        T ind       = JosephusCalculator<T, K>::getIndex();
        range_[ind] = 0;
}

template<typename T, typename K>
void JosephusNaive<T, K>::index_up_() {
        JosephusCalculator<T, K>::increase_index();
        JosephusCalculator<T, K>::modulate_index();
}

template <typename T, typename K>
void JosephusNaive<T, K>::
        solve(){

        while (JosephusCalculator<T, K>::getRun()) { 
                T current_index = JosephusCalculator<T, K>::getIndex();
                if (range_[current_index]) { 
                        K currentOrder = JosephusCalculator<T, K>::getOrderStep() + 1;
                        if (counter_ % currentOrder != 0) {
                                increase_counter_();
                        } else {
                                display(range_[current_index]);
                                JosephusCalculator<T, K>::decrease_iterations_();
                                remove_element_();
                                reset_counter_();
                        }
                }
                index_up_();
        }
}


// better do via inheritance -- continue
template <typename T, typename K>
class JosephusV1 : public JosephusCalculator<T, K> {
public:
        JosephusV1(size_t n, ui64 k) :
        JosephusCalculator<T, K> (n, k),
        step(-1)
        {
                init();
        }

        void init() override {
                T size_ = JosephusCalculator<T, K>::getSize();
                for (size_t element = 1; element <= size_; element++) {
                        Jcollection_.insert(element);
                }
        }

        void solve() override;

        void empty_collection_();

private:
        int64_t step;
        indexed_set Jcollection_;
        queue<T> removal_waiting_elements_;
};

template <typename T, typename K>
void JosephusV1<T,K>::
        solve(){
        T current_index = JosephusCalculator<T, K>::getIndex();

        while(JosephusCalculator<T, K>::getRun()) { 

                if (step == -1) {
                        current_index += JosephusCalculator<T, K>::getOrderStep();
                } else {
                        current_index = step;
                        step          = -1;
                }
                
                if (current_index < JosephusCalculator<T, K>::getSize()) { 
                        auto element  = Jcollection_.find_by_order(current_index);
                        removal_waiting_elements_.push(*element);
                        display(*element);
                        JosephusCalculator<T, K>::decrease_iterations_();
                        current_index++;
                } else {
                        step          = current_index - JosephusCalculator<T, K>::getSize();
                        empty_collection_();
                        JosephusCalculator<T, K>::setSize(Jcollection_.size());
                } 
        }
}

template <typename T, typename K>
void JosephusV1<T, K>::
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

template <typename T, typename K>
void test_Naive(T n, K k) {
        JosephusNaive<T, K> jc(n, k);
        jc.solve();
}

template <typename T, typename K>
void test_V1(T n, K k) {
        JosephusV1<T, K> jc(n, k);
        jc.solve();
}

int main() {
        desyncio();
        size_t n;
        ui64 k; 
        cin >> n >> k;

        /*{
                LOG_DURATION("Naive running time:");
                test_Naive(n, k);
        }

        {
                LOG_DURATION("V1 running time:");
                test_V1(n, k);
        }*/

        test_V1(n, k);

        return 0;
}
