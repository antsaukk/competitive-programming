/*
There are n children who want to go to a Ferris wheel, and your task is to find a gondola for each child.

Each gondola may have one or two children in it, and in addition, the total weight in a gondola may not exceed x.

You know the weight of every child.

What is the minimum number of gondolas needed for the children?
 
INPUT:
The first input line contains two integers n and x: the number of children and the maximum allowed weight.

The next line contains n integers p1,p2,…,pn: the weight of each child.

OUTPUT:

Print one integer: the minimum number of gondolas.
 
CONSTRAINTS:
1 <= n <= 2*10^5
1 <= x <= 10^9
1 <= pi <= x

EXAMPLE:

Input:
4 10
7 2 3 9

Output:
3

SOLUTION: 

Greedy algorithm: sort the children by weight and try 
the heaviest + lighest. If weight exceeeds capacity, 
choose the heaviest.

VERIFY HERE:

https://cses.fi/problemset/task/1090/

*/

#include <iostream>
#include <stdlib.h>
#include <algorithm>

#define READ(x) (cin >> (x))

using namespace std;
using ui64 = uint64_t;

constexpr ui64 TERMINATION = 10'000'000'001;

inline void desyncio() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

template <typename T>
inline void PrintOut(T value, string const& delimeter = "") {
	cout << value << delimeter;
}

template  <typename T>
inline bool CheckBounds(const size_t parameter, const T upperBound) {
    return (parameter < 1 || parameter > upperBound);
}

template <typename T>
struct range {
	explicit range(const size_t n, const T x) :
	size_(n),
	upperBound(x)
	{
		sequence = static_cast<T* >(malloc(sizeof(T) * (n+1)));
		*(sequence + n) = TERMINATION;
	}

	~range() {
		free(sequence);
	}

	void Init() {
		for (size_t i = 0; i < size_; i++) {
			T p; 
			READ(p);

			*(sequence + i) = p;
		}
	}

	void SortRange() {
		sort(sequence, sequence + size_);
	}

	inline T GetValue(const size_t index) const {
		return *(sequence + index);
	}

	inline size_t GetSize() const {
		return size_;
	}

	inline T GetUpperBound() const {
		return upperBound;
	}

private:
	const size_t size_;
	const T upperBound;

	T *sequence;
};

template <typename T>
size_t BalanceWeights(range<T>& numbers) {
	numbers.SortRange();

	size_t pairCounter = 0;

	int start   	   = 0;
	int end	   	   = numbers.GetSize() - 1;

	while (start <= end) {

		T candidate = numbers.GetValue(end) + numbers.GetValue(start);

		if (candidate <= numbers.GetUpperBound()) {
			start++;
			end--;
		} else {
			end--;
		}

		pairCounter++;
	}

	return pairCounter;
}

void run() {
	size_t n;
	ui64 x; 

	READ(n);
	READ(x);

	if (CheckBounds(n, 200'000u) || CheckBounds(x, 1'000'000'000u))
		throw invalid_argument("Incorrect parameter n!");

	range numbers(n, x);
	numbers.Init();

	PrintOut(BalanceWeights(numbers));
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