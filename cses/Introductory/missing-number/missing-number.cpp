/*
You are given all numbers between 1,2,…,n except one. Your task is to find the missing number.
 
INPUT:
The first input line contains an integer n.

The second line contains n−1 numbers. Each number is distinct and between 1 and n (inclusive).

OUTPUT:

Print the missing number.
 
CONSTRAINTS:
2 <= n <= 2*10^5

EXAMPLE:

Input:
5
2 3 1 5

Output:
4

VERIFY HERE:

https://cses.fi/problemset/task/1083/

*/

#include <iostream>
#include <vector>
#include <algorithm>

#define READ(x) (cin >> (x))

using namespace std;

inline void desyncio() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

template <typename T>
inline void PrintOut(T value, string const& delimeter = "") {
	cout << value << delimeter;
}

inline bool CheckBounds(const size_t parameter) {
    return (parameter < 2 || parameter > 200'000);
}

template <typename T>
T solve(vector<T>& numbers) {
	size_t i = 0;
	while (numbers[i] == 1){
		i++;
	}

	return i + 1;
}

void ReadStream(vector<int>& numbers) {
	for (size_t i = 1; i < numbers.size(); i++) {
		size_t x; 
		READ(x);

		numbers[x-1] = 1;
	}
}

void run() {
	size_t n; 

	READ(n);

	if (CheckBounds(n))
		throw invalid_argument("Incorrect parameter n!");

	vector<int> numbers(n);
	ReadStream(numbers);

	PrintOut(solve(numbers));
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