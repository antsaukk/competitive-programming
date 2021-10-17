#include <iostream>
#include <vector>
#include <cmath>
#include <limits.h>

#define i64 int64_t
#define INF INT_MAX

using namespace std;

i64 threshold = 0;
i64 source = 0;
int n, m;
vector<vector<pair<i64, i64>>> graph;
//vector<vector<pair<i64, i64>>> rGraph;
vector<int> visited;

void falsify() {
	for(size_t i = 0; i < visited.size(); i++)
		visited[i]=false;
}

void potentiate() {
	threshold = pow(2, static_cast<i64>(floor(log(threshold)/log(2))));
}

int index(int ind) {
	return ind - 1;
}

bool scalingCondition(i64 capacity, bool visited) {
	//return (capacity >= threshold && !visited); 
	//return (capacity > threshold && !visited); 
	return (capacity > threshold); 
}

i64 edge(i64 node, size_t ind) {
	return graph[node][ind].first;
}

i64 weight(i64 node, size_t ind) {
	return graph[node][ind].second;
}

void augment(i64 node, size_t ind, i64 flow) {
	graph[node][ind] = make_pair(edge(node, ind), weight(node, ind) - flow);
	graph[node][ind] = make_pair(edge(node, ind), weight(node, ind) - flow);
}

i64 DFS(i64 node, i64 flow) {
	if (node == index(n)) return flow;
	if (visited[node]) return 0;
	visited[node] = true;

	for (size_t ind = 0; ind < graph[node].size(); ind++) {
		auto cap = weight(node, ind);
		if (scalingCondition(cap, visited[edge(node, ind)])){
			i64 f = DFS(edge(node, ind), min(flow, cap));
			if (f > 0) {
				augment(node, ind, f);
				return f;
			}
		}
	}
	return 0;
}


i64 solve() {
	i64 maxflow = 0;
	i64 flow = 0;
	/*while(threshold > 0) {
		do {
			falsify();
			flow = DFS(source, INF);
			maxflow+=flow;
		} while(flow!=0);
		threshold /= 2;
	}*/
	threshold = 0;
	do {
			falsify();
			flow = DFS(source, INF);
			maxflow+=flow;
		} while(flow!=0);
	return maxflow;
}

int main() {
	cin >> n >> m; 
	
	//construct weighted directed graph and reversed graph
	graph.resize(n);
	//rGraph.resize(n);
	visited.resize(n);
	for(int i = 0; i < m; i++) {
		int a, b; i64 c; 
		cin >> a >> b >> c; 
		graph[index(a)].push_back(make_pair(index(b), c));
		rGraph[index(b)].push_back(make_pair(index(a), 0));
		threshold = max(c, threshold);
		//threshold += c;
	}
	potentiate();
	cout << solve();

	return 0;
}