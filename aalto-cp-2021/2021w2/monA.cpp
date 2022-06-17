#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
	size_t n;
	cin >> n;
	vector<int> heights(n); 
	vector<int> walls(n+1);

	int h;
	for(size_t i = 0; i < n; i++) {
		cin >> h;
		heights[i] = h;
	}

	walls[0] = heights[0];
	for(size_t i = 1; i < n; i++) {
		walls[i] = max(heights[i], heights[i-1]);
	}
	walls[n] = heights[n-1];

	int max = 0;
	vector<int> right_scan(n+1);
	for(size_t i = 0; i < n+1; i++) {
		max = max < walls[i] ? walls[i] : max;
		right_scan[i] = max;
 	}

 	max = 0;
 	vector<int> left_scan(n+1);
 	for(int i = n; i >= 0; i--) {
		max = max < walls[i] ? walls[i] : max;
		left_scan[i] = max;
 	}


	int sum = 0;
 	for(size_t i = 1; i < n+1; i++) {
 		sum += min(min(right_scan[i], right_scan[i-1]), min(left_scan[i], left_scan[i-1]));
 	}

 	cout << sum;

	return 0;
}