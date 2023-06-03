#include <vector>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cmath>
#include <omp.h>
 
using i64 = int64_t;
using namespace std;

#define READ(x) (cin >> (x))
 
template <typename T>
void PrintOut(T value, string const& delimeter = "")
{
	cout << value << delimeter;
}

const size_t nextPowerOf2(size_t x)
{
	return pow(2, ceil(log(x)/log(2)));
}

template <typename T>
struct SumSegmentTree
{
	explicit SumSegmentTree(vector<T>& numbers) :
	n_(nextPowerOf2(numbers.size())),
	tree_(2*n_)
	{
		tree_[n_] = numbers[0];
		for (size_t k = n_+1; k < tree_.size(); k++)
		{
			size_t xi = k - n_ < numbers.size();
			tree_[k] = xi * (numbers[k - n_] - numbers[k - n_ - 1]) + 0;
		}

		for (size_t k = n_-1; k >= 1; k--)
		{
			tree_[k] = tree_[2*k] + tree_[2*k+1];
		}
	}


	void change(size_t k, T value)
	{
		k--;
		k += n_;

		tree_[k] += value;

		for (k /= 2; k >= 1; k /= 2)
		{
			tree_[k] = tree_[2*k] + tree_[2*k+1];
		}
	}

	T getSumInRange(T a, T b)
	{
		a--;
		b--;
		a += n_;
		b += n_;

		T sum = 0;

		while (a <= b)
		{
			if (a%2 == 1) sum += tree_[a++];
			if (b%2 == 0) sum += tree_[b--];
			a /= 2; b /= 2;
		}

		return sum;
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
};

template <typename T>
void ReadStream(vector<T>& container)
{
	for (size_t i = 0; i < container.size(); i++) {
		T x; 
		READ(x);
		container[i] = x;
	}
}
 
template <typename T>
void solve(vector<T>& container, size_t q)
{
	SumSegmentTree<T> sumTree(container);

	while(q)
	{
		size_t type; READ(type);

		if (type == 1)
		{
			size_t a, b, u;
			READ(a); READ(b); READ(u);

			if (2*a == sumTree.size() || 2*b == sumTree.size()) {
				sumTree.change(a, +u);
			}
			else {
				sumTree.change(a, +u);
				sumTree.change(b+1, -u);
			}
		}
		else
		{
			size_t k; READ(k);
			PrintOut(sumTree.getSumInRange(1, k), "\n");
		}
		q--;
	}
}
 
inline void desyncio()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
}

void run()
{
	size_t n, q;
	READ(n);
	READ(q);

	vector<i64> v(n);
	ReadStream(v);

	solve(v, q);
}
 
int main()
{
	desyncio();
	try {
		run();
	} catch (const invalid_argument& exception) {
		cerr << exception.what() << "\n";
		return -1;
	}
	
	return 0;
}
