#include <iostream>
#include <vector>
#include <deque>
#include <cmath>

using namespace std;

int main() {
	int n;
	cin >> n;

	if (n==0) {
		cout << 0 << endl;
		return 0;
	}

	vector<int> w(n);
	for(int i = 0; i < n; i++){
		cin >> w[i];
	}

	if (w.size()==1) {
		cout << w[0] << endl;
		return 0;
	}

	vector<int> selected_nodes(n); 
	selected_nodes[0] = w[0]; 
	selected_nodes[1] = w[1]; 
	for(int i = 2; i < n; i++) {
		selected_nodes[i] = max(selected_nodes[i-1], selected_nodes[i-2] + w[i]);
	}

	int i = n - 1;
	deque<int> mis;
	while(i >= 1) {
		if (selected_nodes[i] == selected_nodes[i-1])
			i--;
		else {
			mis.push_back(i);
			i-=2;
			if (i==0) mis.push_back(i);
		}
	}

	for(auto node : mis) {
		cout << node << " "; 
	}

	cout << endl << "MIS: " << selected_nodes[n-1] << endl;

}