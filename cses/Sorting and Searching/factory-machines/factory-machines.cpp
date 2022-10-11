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
#include <vector>
#include <cstdlib>
 
#define READ(x) (cin >> (x))
 
using namespace std;
using big_int64 = int64_t;
 
inline void desyncio() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}
 
template <typename T>
void PrintOut(T value, string const& delimeter = "") {
	cout << value << delimeter;
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
void solve(vector<T>& numbers, const T t) {
	auto sorted = numbers;
	sort(sorted.begin(), sorted.end());

	vector<T>schedule(numbers.size());

	T remaining_time = t;

	T final_maximum_duration = 0;


	while (remaining_time > 0) {

		T maximum_duration = 10'000'000'01;
		T duration = 0;
		T machine = 0;

		for (size_t i = 0; i < sorted.size(); i++) {
			if (sorted[i] + schedule[i] < maximum_duration) {
				maximum_duration = sorted[i] + schedule[i];
				duration = sorted[i];
				machine = i;
			}
		}

		schedule[machine] += duration;

		remaining_time--;

		final_maximum_duration = maximum_duration;
	}

	/*for (size_t i = 0; i < schedule.size(); i++) {
		for (big_int64 j = 0; j < schedule[i]; j++) {
			PrintOut("# | ");
		}
		PrintOut("\n");
	}*/

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