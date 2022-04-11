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
#include <numeric>

#define ui64 uint64_t

using namespace std;

template<typename T>
void display(T val) {
        cout << val << " ";
}

template <typename T,
          typename K>
class JosephusCalculator {
public:
        explicit JosephusCalculator(size_t n,
                                    ui64 k) :
        n_(n),
        counter_(1u),
        run_(n),
        index_(0u),
        k_(k),
        range_(n)
        {
                iota(range_.begin(), range_.end(), 1);
        }

        void increase_counter_()        { counter_++; }

        void reset_counter_()           { counter_ = 1; }

        void decrease_iterations_()     { run_--; }

        void remove_element_()          { range_[index_] = 0; }

        void index_up_()                { index_++; index_ %= n_; }

        void solve_naive_();

private:
        T n_            = 0;
        T counter_      = 0;
        T run_          = 0;
        T index_        = 0;
        K k_            = 0;
        vector<T> range_;
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
        jc.solve_naive_();

        return 0;
}
