#include <iostream>
#include <cmath>
#include <limits.h>
using namespace std;

int gcd(int a, int b) {
   if (b == 0)
   return a;
   return gcd(b, a % b);
}

int main() {
	size_t k; 
	cin >> k;

	int y, f, s; 


	int mem = INT_MAX; 
	for(size_t i = 0; i < k; i++) {
		cin >> y; 
		cin >> f; 
		cin >> s;
		mem = min(mem, y + f*s/gcd(f, s));
	}

	cout << mem;

	return 0;
}