#include <iostream>
#include <vector>
#include <cmath>
#include <limits.h>

#define i64 int64_t
#define INF INT_MAX

using namespace std;

i64 threshold = 0;
size_t source = 0;
size_t n, m;
vector<i64*> graph;
vector<int> visited;

void falsify() {
	for(size_t i = 0; i < visited.size(); i++)
		visited[i]=false;
}

void potentiate() {
	threshold = pow(2, static_cast<i64>(floor(log(threshold)/log(2))));
}

size_t index(size_t ind) {
	return ind-1;
}

bool scalingCondition(i64 capacity) {
	return (capacity >= threshold); 
}

i64 weight(size_t node, size_t edge) {
	return graph[node][edge];
}

void augment(size_t node, size_t edge, i64 flow) {
	graph[node][edge] = weight(node, edge) - flow;
	graph[edge][node] = weight(edge, node) + flow;
}

i64 DFS(size_t node, i64 flow) {
	if (node == index(n)) return flow;
	if (visited[node]) return 0;
	visited[node] = true;

	for (size_t edge = 0; edge < n; edge++) {
		auto cap = weight(node, edge);
		if (scalingCondition(cap)){
			i64 f = DFS(edge, min(flow, cap));
			if (f > 0) {
				augment(node, edge, f);
				return f;
			}
		}
	}
	return 0;
}

// Edmond's Karp search algorithm
i64 solveEdmondKarp() {return 0;}

//with dfs that uses scaling solution
i64 solveScaling() {
	i64 maxflow = 0;
	i64 flow = 0;
	while(threshold > 0) {
		do {
			falsify();
			flow = DFS(source, INF);
			maxflow+=flow;
		} while(flow!=0);
		threshold /= 2;
	}
	return maxflow;
}

//naive dfs without scaling condition
i64 solve() {
	threshold = 0;
	i64 maxflow = 0;
	i64 flow = 0;
	do {
		falsify();
		flow = DFS(source, INF);
		maxflow+=flow;
	} while(flow!=0);
	return maxflow;
}

void allocate(){
	graph.resize(n);
	for(size_t i = 0; i < n; i++) {
		graph[i] = new i64[n];
	}
}

void freemem(){
	for(size_t i = 0; i < n; i++) 
		delete[] graph[i];
}

void construct(size_t a, size_t b, i64 c){
	graph[index(a)][index(b)] += c; // =
	graph[index(b)][index(a)] = 0;
}

int main() {
	cin >> n >> m;
	
	//construct weighted directed graph and reversed graph
	allocate();
	visited.resize(n);
	for(size_t i = 0; i < m; i++) {
		size_t a, b; i64 c; 
		cin >> a >> b >> c;
		construct(a, b, c);
		threshold = max(c, threshold);
	}
	potentiate();
	cout << solveScaling();
	freemem();

	return 0;
}