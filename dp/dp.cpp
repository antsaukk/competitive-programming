#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;


pair<vector<int>, int> reconstruct(const vector<int>& nodes) {
	int i = nodes.size() - 1;
	vector<int> mis;
	while(i >= 1) {
		if (nodes[i] == nodes[i-1]) { i--; }
		else { mis.push_back(i); i-=2; }
		if (i==0) { mis.push_back(i); }
	}

	for(auto node : mis) {
		cout << node << " "; 
	}
	cout << "\n" << nodes[nodes.size()-1] << "\n";

	return make_pair(mis, nodes[nodes.size()-1]);
}

//dynamic programming algorithm to find
//maximum weight independent set in a path in O(n)
pair<vector<int>, int> mis_in_path(const vector<int>& weights, size_t n) {
	if (n==0) { cout << "0\n"; return make_pair(vector({-1}), 0); }
	else if (n==1) { cout << weights[0] << "\n"; return make_pair(vector({0}), weights[0]); }
		
	vector<int> selected_nodes(n);

	selected_nodes[0] = weights[0]; 
	selected_nodes[1] = weights[0] > weights[1] ? weights[0] : weights[1]; 
	for(size_t i = 2; i < n; i++) {
		selected_nodes[i] = max(selected_nodes[i-1], selected_nodes[i-2] + weights[i]);
	}

	return reconstruct(selected_nodes);
}

int get_index(const vector<int>& weights, int elem){ 
	return (find(weights.begin(), weights.end(), elem) - weights.begin());
}

/*pair<vector<int>, int> mvc_in_path(const vector<int>& weights, size_t n) {
	if (n==0) { cout << "0\n"; return make_pair(vector({-1}), 0); }
	else if (n==1) { cout << weights[0] << "\n"; return make_pair(vector({0}), weights[0]); }
	else if (n==2) {
		int element = min(weights[0], weights[1]); 
		cout << element << "\n";
		int ind = get_index(weights, element);
		return make_pair(vector({ind}), element);
	}
		
	vector<int> selected_nodes;

	size_t i = 2; 
	int sum
	while(i < n) {
		if (weights[i] + weights[i-2] < weights[i-1]){

		}
	}

	return reconstruct(selected_nodes);
}*/

