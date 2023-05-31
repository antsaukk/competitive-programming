/*
A factory has n machines which can be used to make products. Your goal is to make a total of t products.

For each machine, you know the number of seconds it needs to make a single product.

The machines can work simultaneously, and you can freely decide their schedule.

What is the shortest time needed to make t products?
 
INPUT:

The first input line has two integers n and t: the number of machines and products.

The next line has n integers k1,k2,…,kn: the time needed to make a product using each machine.

OUTPUT:

Print one integer: the minimum time needed to make t products.
 
CONSTRAINTS:
1 <= n <= 2*10^5
1 <= t <= 10^9
1 <= ki <= 10^9

EXAMPLE:

Input:
3 7
3 2 5

Output:
8

VERIFY HERE:

https://cses.fi/alon/task/1620

*/

#include <iostream>
#include <algorithm>
#include <limits>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <cassert>
 
#define READ(x) (cin >> (x))
 
using namespace std;
using big_int64 = int64_t;

template <typename T>
void PrintOut(T value, string const& delimeter = "") {
	cout << value << delimeter;
}

const size_t nextPowerOf2(size_t x)
{
	return pow(2, ceil(log(x)/log(2)));
}

template <typename T>
struct MinSegmentTree {
	explicit MinSegmentTree(vector<T>& numbers) :
	n_(nextPowerOf2(numbers.size())),
	tree_(2*n_),
	init_(2*n_)
	{
		for (size_t k = n_; k < tree_.size(); k++)
		{
			size_t xi = k - n_ < numbers.size();
			tree_[k] = xi * numbers[k - n_] + (!xi) * numeric_limits<T>::max();
			init_[k] = tree_[k];
		}

		for (size_t k = n_-1; k >= 1; k--)
		{
			tree_[k] = min(tree_[2*k], tree_[2*k+1]);
		}
	}


	void change(size_t k)
	{
		k = getIndexOfMin();
		tree_[k] += init_[k];

		for (k /= 2; k >= 1; k /= 2)
		{
			tree_[k] = min(tree_[2*k], tree_[2*k+1]);
		}
	}

	const T getMin() const
	{
	    return tree_[1];
	}

	T getMinInRange(T a, T b)
	{
		a += n_;
		b += n_;

	    T x = tree_[a];

	    while (a <= b)
	    {
	    	if (a%2 == 1) x = min(x, tree_[a++]);
	    	if (b%2 == 0) x = min(x, tree_[b--]);
	    	a /= 2; b /= 2;
	    }
	    return x;
	}

	const size_t getIndexOfMin() const
	{
		size_t k = 1;
		while (k < size()/2)
		{
			size_t xi = tree_[2*k] < tree_[2*k+1];
			k = xi * 2 * k + (!xi) * (2*k + 1);
		}

		assert(k >= 0);
		assert(k <= size() - 1);

		return k;
	}

	const size_t size() const
	{
		return 2*n_;
	}

	const T element(size_t index) const
	{
		return tree_[index];
	}

private:
	size_t n_;
	vector<T> tree_;
	vector<T> init_;
};
 
inline void desyncio() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}
 
template <typename T>
void ReadStream(vector<T>& container) {
	for (size_t i = 0; i < container.size(); i++) {
		T x; 
		READ(x);
 
		container[i] = x;
	}
}

template <typename T>
void debug(MinSegmentTree<T>& segtree)
{
	PrintOut(segtree.size(), " - size of segment tree\n");
	for (size_t i = 0; i < segtree.size(); i++)
	{
		PrintOut(segtree.element(i), " ");
	}
	PrintOut("\n");
	PrintOut(segtree.getIndexOfMin(), " - index of min\n");
}
 
template <typename T>
void solve(vector<T>& numbers, const T t) {
	MinSegmentTree<T> schedule(numbers);

	T remaining_products = t;
	T final_maximum_duration = 0;

	while (remaining_products > 0) { // t
		T minima = schedule.getMin();

		final_maximum_duration = minima;

		schedule.change(1); // log N

		remaining_products--;
	}

	PrintOut(final_maximum_duration);
}
 
void run() {
	size_t n;
	big_int64 t;
	READ(n);
	READ(t);
 
	vector<big_int64> numbers(n);
	ReadStream(numbers);
 
	solve(numbers, t);
}
 
int main() {
	desyncio();
 
	try {
		run();
	} catch (const invalid_argument& exception) {
		cerr << exception.what() << "\n";
		return -1;
	}
    
    return 0;
}