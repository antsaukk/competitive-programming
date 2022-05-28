/*
Given an array of n integers,
your task is to find for each array position the nearest position to its left having a smaller value.

INPUT:
The first input line has an integer n: the size of the array.

The second line has n integers x1,x2,…,xn: the array values.

OUTPUT:

Print n integers: for each array position the nearest position with a smaller value.
If there is no such position, print 0.

CONSTRAINTS:
1 <= n <= 2*10^5
1 <= xi <= 10^9

RESULT:
https://cses.fi/alon/result/3998722/
*/

#include <iostream>
#include <vector>
#include <stack>

#define ui64 uint64_t

template <typename T>
using Pair = typename std::pair<T, size_t>;

template<typename T>
void display(T val){
	std::cout << val << " ";
}

enum StackState {
	EMPTY,
	NONEMPTY
};

template <typename T>
struct HolderReader {
	explicit HolderReader(size_t n) :
	n_(n),
	container(n),
	state(StackState::EMPTY)
	{
		read();
	}

	inline void read() {
		for (size_t i = 0; i < n_; i++)
			std::cin >> container[i];
	}

	inline void stackify(T element, size_t index) {
		minimal_heap.push({element, index});
	}

	inline void destackify() {
		minimal_heap.pop();
		check_stack();
	}

	inline void set_state(StackState st) {
		state = st;
	}

	inline void check_stack() {
		if (minimal_heap.empty()) {
			set_state(StackState::EMPTY);
		}
	}

	inline StackState access_state() {
		return state;
	}

	inline const T access_element(const size_t index) const {
		return container[index];
	}

	inline const T access_min_element() const {
		return minimal_heap.top().first;
	}

	inline const size_t access_min_index() const {
		return minimal_heap.top().second;
	}


private:
	size_t n_;
	std::vector<T> container;
	std::stack<Pair<T>> minimal_heap;
	StackState state; 
};

/*
	DP algorithm:
	Starts with empty table and add the first element from the sequence.
	Then iterate over the sequence from left to right removing element from the table
	if it is greater of equal to current element, otherwise adding current element to the table
	and displaying the position of the minimal element from the table. 
	Works in
*/
inline void solve() {
	size_t n; 
	std::cin >> n; 
	HolderReader<ui64> counter(n);

	counter.stackify(counter.access_element(0), 1);
	counter.set_state(StackState::NONEMPTY);

	display(0);

	for (size_t i = 1; i < n; i++) {

		while (counter.access_state() == StackState::NONEMPTY) {
			if (counter.access_min_element() >= counter.access_element(i)) {
				counter.destackify();
			} else {
				display(counter.access_min_index());
				counter.stackify(counter.access_element(i), i+1);
				break;
			}
		}

		if (counter.access_state() == StackState::EMPTY) {

			counter.stackify(counter.access_element(i), i+1);
			counter.set_state(StackState::NONEMPTY);

			display(0);
		}
	}
}

int main() {
	solve();
	return 0;
}