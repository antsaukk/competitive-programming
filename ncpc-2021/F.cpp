#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int nCk(int n, int k) {
    if (k > n / 2)
        k = n - k;
 
    int answer = 1;
    for (int i = 1; i <= k; i++) {
        answer *= (n - k + i);
        answer /= i;
    }
 
    return answer;
}

double bin(int n, int k, double p) {
    return nCr(n, k) * pow(p, k) * pow(1 - p, n - k);
}

int main() {
	int n, k; 
	cin >> n >> k; 
	double p; 
	cin >> p;

	while

	int N = n;
	int64_t Ex = 0;
	double P = bin(n, k, p);
	while(true) {
		//Ex += N * P
	}



	return 0;
}