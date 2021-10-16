#include <iostream>
#include <vector>
#include <limits.h>

#define i64 int64_t
#define INF INT_MAX

using namespace std;

int threshold = 0;
int n, m;
vector<vector<pair<i64, i64>>> graph;
vector<vector<pair<i64, i64>>> rGraph;
vector<int> visited;
int fl = 0; 

void falsify() {
	for(size_t i = 0; i < visited.size(); i++)
		visited[i]=false;
}

int index(int ind) {
	return ind - 1;
}

i64 capacity(i64 val) { 
	return val - fl; 
}

i64 DFS(i64 node, i64 flow) {
	if (node == n) return flow; //or visited???

	cout << "in dfs\n";

	visited[node] = true;
	for (size_t ind = 0; ind < graph[node].size(); ind++) {
		auto cap = capacity(graph[node][ind].second); //update capacity
		cout << cap << "\n";
		if (cap >= threshold && !visited[graph[node][ind].first]){
			i64 f = DFS(graph[node][ind].first, min(flow, cap));
			cout << f << " -f\n";
			if (f > 0) {
				graph[node][ind] = make_pair(graph[node][ind].first, f);
				fl += f;
				return f;
			}
		}
	}
	return 0;
}


i64 solve() {
	i64 maxflow = 0;
	i64 source = 0;
	while(threshold > 0) {
		i64 flow = 0;
		cout << "here\n";

		falsify();
		flow = DFS(source, INF); //<--- here is the problem
		maxflow+=flow;

		cout << maxflow << " - mf\n";

		threshold /= 2;

		cout << threshold << " - t\n";
	}
	return maxflow;
}

int main() {
	cin >> n >> m; 
	
	//construct weighted directed graph and reversed graph
	graph.resize(n);
	rGraph.resize(n);
	visited.resize(n);
	cout << graph.size() << rGraph.size() << visited.size() << "\n";
	for(int i = 0; i < m; i++) {
		int a, b, c; 
		cin >> a >> b >> c; 
		graph[index(a)].push_back(make_pair(index(b), c));
		rGraph[index(b)].push_back(make_pair(index(a), 0));
		threshold += c;
		cout << threshold << "\n";
	}

	cout << solve();

	return 0; 
}