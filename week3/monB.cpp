#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;


pair<vector<int64_t>, int64_t> reconstruct(const vector<int64_t>& nodes) {
	int i = nodes.size() - 1;
	vector<int64_t> mis;
	while(i >= 1) {
		if (nodes[i] == nodes[i-1]) { i--; }
		else { mis.push_back(i); i-=2; }
		if (i==0) { mis.push_back(i); }
	}

	return make_pair(mis, nodes[nodes.size()-1]);
}

pair<vector<int64_t>, int64_t> mis_in_path_max(const vector<int64_t>& weights, size_t start, size_t end) {	
	vector<int64_t> selected_nodes(end-start);

	selected_nodes[0] = weights[start]; 
	selected_nodes[1] = weights[start] > weights[start+1] ? weights[start] : weights[start+1]; 
	for(size_t i = start+2; i < end; i++) {
		selected_nodes[i] = max(selected_nodes[i-1], selected_nodes[i-2] + weights[i]);
	}

	return reconstruct(selected_nodes);
}


pair<vector<int64_t>, int64_t> mis_in_path_min(const vector<int64_t>& weights, size_t start, size_t end) {	
	vector<int64_t> selected_nodes(end-start);

	selected_nodes[0] = weights[start]; 
	selected_nodes[1] = weights[start] < weights[start+1] ? weights[start] : weights[start+1]; 
	for(size_t i = start+2; i < end; i++) {
		selected_nodes[i] = min(selected_nodes[i-1], selected_nodes[i-2] + weights[i]);
	}

	return reconstruct(selected_nodes);
}


int main() {
	size_t n;
	cin >> n;

	vector<int64_t> nums(n);
	vector<int64_t> nums2(n);
	for(size_t i = 0; i < n; i++) {
		int64_t s; 
		cin >> s;
		nums[i] = s;
		nums2[i] = s;
	}
	
	auto mis1 = mis_in_path_max(nums, 0, n-1);
	auto mis2 = mis_in_path_max(nums, 1, n);

	int64_t sum1max = mis1.second;
	int64_t sum2max = mis2.second;

	if (sum1max > sum2max) {
		for(auto ind : mis1.first) {
			nums2[ind] = 10000000;
		}
	} else {
		for(auto ind : mis2.first) {
			nums2[ind] = 10000000;
		}
	}

	auto mis3 = mis_in_path_min(nums2, 0, n-1);
	auto mis4 = mis_in_path_min(nums2, 1, n);

	int64_t sum1min = mis3.second;
	int64_t sum2min = mis4.second;

	cout << max(sum1max, sum2max) - min(sum1min, sum2min);

	return 0;
}