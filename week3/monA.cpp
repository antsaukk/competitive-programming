#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
	size_t n;
	cin >> n;

	vector<int> nums(n);
	for(size_t i = 0; i < n; i++) {
		cin >> nums[i];
	}

	int64_t steps = 0;
	for(size_t i = 1; i < n; i++) {
		while (nums[i] < nums[i-1]){
			nums[i]++; 
			steps++; 
		}
	}

	cout << steps;

	return 0;
}