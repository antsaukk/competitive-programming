#include <vector>
#include <cmath>
#include <iostream>

/*
Aliases
*/
using namespace std;
using i64 = int64_t;

template <typename T>
using book = pair<T, T>;

/*
Utilities
*/
template<typename T>
inline void display(T val){
	cout << val << " ";
}

/*
desynchronize input/output buffers
to improve computational speed
*/
inline void desyncio() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
}

/*
You are in a book shop which sells n different books.
You know the price and number of pages of each book.

You have decided that the total price of your purchases will be at most x.
What is the maximum number of pages you can buy? You can buy each book at most once.

INPUT:
The first input line contains two integers n and x:
the number of books and the maximum total price.

The next line contains n integers h1,h2,…,hn: the price of each book.

The last line contains n integers s1,s2,…,sn: the number of pages of each book.
 
OUPUT:
Print one integer: the maximum number of pages.

CONSTRAINTS:
1 <= n <= 1000
1 <= x <= 10^5
1 <= h_i, s_i <= 1000

SOLUTION: 
Dynamic programming
 
VERIFY:
https://cses.fi/problemset/task/1158/
*/

/*
Structure that handles house keeping operations of a single book
*/
template <typename T>
struct Book {
	explicit Book(T pages=0,
				  T price=0)
	{
		b = {pages, price};
	}

	inline const T Pages() const {
		return b.first;
	}

	inline const T Price() const {
		return b.second;
	}

private:
	book<T> b; 
};

/*
Structure that handles storage of books' with pages and prices
*/
template <typename T,
	typename K>
struct BookShelf {
	explicit BookShelf(T n) : N(n), shelf(n) {}

	inline void Read() {
		for (size_t i = 0; i < N; i++) {
			K price;
			cin >> price;
			shelf[i] = Book<K>(0, price);
		}

		for (size_t i = 0; i < N; i++) {
			K page;
			cin >> page;
			shelf[i] = Book<K>(page, GetBook(i).Price());
		}
	}

	inline const Book<K>& GetBook(T index) const {
		return shelf.at(index);
	}

	inline const T Size() const {
		return N;
	}

private:
	T N;
	vector<Book<K>> shelf;
};

/*
Structure that handles dynamic programming grid
*/
template <typename T>
struct DPtable {
	explicit DPtable(T x) :
	X(x),
	dp(x+1)
	{}	

	inline void SetDP(T index, T value) {
		dp[index] = value;
	}

	inline const T GetMaximum() const {
		return dp[X];
	}

	inline const T DP(T index) const {
		return dp[index];
	}

	inline const T MaximumCost() const {
		return X;
	}

private:
	T X;
	vector<T> dp;
};


/*
Dynamic programming algorithm:
Let Pg be the set of pages, Pr be the set of prices
and X maximum price that we can spend on books.

Then the problem is equivalent to
		max_{p \in Pg} sum(p)
		s.t. sum_{p \in Pr} sum(p) <= X

And observe that this problem is reducible to the basic 
knapsack maximization problem. 

The solution to maximization version of knapsack is given by:
Let be B = {(price_i, page_i)}, i = 1, ...,N 
be the set of tuples where first value 
is price of book i and page is the number of pages in book i.
Let solution(N, X) be two dimensional grid where value solution(n, x) is 
maximum number of pages we can by if we are choosing from n - 1 first books. 
Then, we can recursively fill solution() using
		solution(n,x) = max(solution(n-1, x),
							page_i + solution(n - 1, x - price_i))
which is based on the observation that we can either choose book_i and consider
the choosing from other books with x - price_i money left, or we can just leave 
previously computed subsolution if it is more optimal. Then solution(N, X) contains
maximum amount of pages we can buy withtin the cost constraint. However,
here we are only allowed to use 512MB of the memory and according to constraints
on N and X, the size of the grid might be 1000 * 100000, which clearly takes more
memory. We can substitute 2d grid by 1d grid and iterate from right to left updating 
maximum number of pages we can by is we are choosing book_i for each book_i. 
*/
template <typename T,
	typename K>
void solve(DPtable<T>& Grid,
	BookShelf<K, T>& Shelf) {

	for (size_t i = 1; i <= Shelf.Size(); i++) {

		auto pages = Shelf.GetBook(i - 1).Pages();
		auto price = Shelf.GetBook(i - 1).Price();


		for (int j = Grid.MaximumCost(); j >= 0; j--) {
			if (price <= j) {
				auto candidate = max(Grid.DP(j), pages + Grid.DP(j - price));
				Grid.SetDP(j, candidate);
			} else {
				Grid.SetDP(j, Grid.DP(j));
			}
			
		}
	}
}

void run() {
	desyncio();
 
	size_t n;
	i64 x;
	cin >> n >> x;

	DPtable<i64> Grid(x);

	BookShelf<size_t, i64> Shelf(n);
	Shelf.Read();

	solve(Grid, Shelf);

	display(Grid.GetMaximum());
}
 
int main() {
	run();
	return 0;
}