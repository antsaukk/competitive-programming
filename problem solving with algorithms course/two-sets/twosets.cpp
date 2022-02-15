/*
Your task is to divide the numbers 1,2,…,n into two sets of equal sum.

INPUT:
The only input line contains an integer n.

OUTPUT:
Print "YES", if the division is possible, and "NO" otherwise.

After this, if the division is possible, print an example of how to create the sets. 
First, print the number of elements in the first set followed by the elements themselves in a separate line, 
and then, print the second set in a similar way.

CONSTRAINTS:
1 <= n <= 10^6
RESULT:
https://cses.fi/alon/result/3544187/
*/

#include <iostream>
#include <vector>
#include <numeric>

#define ui64 uint64_t

using namespace std;

template<typename T>
void display(T val){
        cout << val;
}


//helper object to handle sets of numbers
template <typename T>
struct TwoSets {
        explicit TwoSets(size_t N) : 
        A_(N),
        B_(N)
        {}

        T get_sum() { return sum; }

        void add_to_sum(T inc) {
                sum += inc;
        }

        void add_to_A(T element) {
                A_[a_size] = element;
                a_size++;
        }

        void add_to_B(T element) {
                B_[b_size] = element;
                b_size++; 
        }

        T get_size_of_A() { return a_size; }

        T get_size_of_B() { return b_size; }

        // ugly function
        void results() {
                display(get_size_of_A());
                display("\n");
                for(size_t i = 0; i < get_size_of_A(); i++) {
                        display(A_[i]); 
                        display(" "); 
                }
                display("\n");
                display(get_size_of_B());
                display("\n");
                for(size_t i = 0; i < get_size_of_B(); i++) {
                        display(B_[i]); 
                        display(" "); 
                }
        }

private:
        T sum = 0;     
        vector<T> A_;
        vector<T> B_;
        T a_size = 0; 
        T b_size = 0; 
};

// greedily select the results
template<typename T>
void select(T n, T csum){
      TwoSets<T> obj{n};
      for(ui64 i = n; i > 0; i--) {
        if (obj.get_sum() + i <= csum/2) {
                obj.add_to_sum(i); 
                obj.add_to_A(i); 
        } else {
                obj.add_to_B(i);
        }
      }
      obj.results();
}

// \sum_from 1 to n = n * (n + 1) / 2
template<typename T>
T accumulate(T n) {
        return n * (n + 1) / 2;
}

// check if the \sum_from 1 to n = 0 mod 2
template<typename T>
void solve(T n){
        T csum = accumulate(n);
        if (!(csum%2)) {
                display("YES\n");
                select(n, csum);
        } else display("NO\n");
}

int main() {
        ui64 n;
        cin >> n;

        solve(n);
        return 0;
}
