#include <vector>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <cstdlib>
#include <cmath>
 
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
struct MaxSegmentTree
{
	explicit MaxSegmentTree(vector<T>& numbers) :
	n_(nextPowerOf2(numbers.size())),
	tree_(2*n_)
	{
		for (size_t k = n_; k < tree_.size(); k++)
		{
			size_t xi = k - n_ < numbers.size();
			tree_[k] = xi * numbers[k - n_] + (!xi) * numeric_limits<T>::min();
		}

		for (size_t k = n_-1; k >= 1; k--)
		{
			tree_[k] = max(tree_[2*k], tree_[2*k+1]);
		}
	}


	void update(size_t k, T value)
	{
		tree_[k] -= value;

		for (k /= 2; k >= 1; k /= 2)
		{
			tree_[k] = max(tree_[2*k], tree_[2*k+1]);
		}
	}

	size_t traverseDown(T group)
	{
		T current_max = getMax();
		size_t k = 1;

		if (group > current_max) return 0;

		while (k < n_)
		{
			T left = element(2*k);
			T right = element(2*k + 1);

			T ldiff = left - group;

			size_t xi = ldiff >= 0;

			k = xi * 2*k + (!xi) * (2*k + 1);
			current_max = xi * left + (!xi) * right;
		}

		update(k, group);
		k++;
		k -= n_;

		return k;
	}

	const T getMax() const
	{
		return tree_[1];
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
void solve(vector<T>& hotels, vector<T>& groups)
{
	MaxSegmentTree<T> maxTree(hotels);

	for (const auto group : groups)
	{
		size_t h = maxTree.traverseDown(group);
		PrintOut(h, " "); 
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
	size_t n, m;
	READ(n);
	READ(m);

	vector<i64> hotels(n);
	ReadStream(hotels);

	vector<i64> groups(m);
	ReadStream(groups);

	solve(hotels, groups);
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