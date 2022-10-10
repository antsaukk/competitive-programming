/*
Consider a network consisting of n computers and m connections. Each connection specifies how fast a computer can send data to another computer.

Kotivalo wants to download some data from a server. What is the maximum speed he can do this, using the connections in the network?
 
INPUT:

The first input line has two integers n and m: the number of computers and connections.
The computers are numbered 1,2,…,n. Computer 1 is the server and computer n is Kotivalo's computer.

After this, there are m lines describing the connections.
Each line has three integers a, b and c: computer a can send data to computer b at speed c.

OUTPUT:

Print one integer: the maximum speed Kotivalo can download data.
 
CONSTRAINTS:
1 <= n <= 500

1 <= m <= 1000

1 <= a,b <= n

1 <= c <= 109

EXAMPLE:

Input:
4 5
1 2 3
2 4 2
1 3 4
3 4 5
4 1 3

Output:
6

VERIFY HERE:

https://cses.fi/problemset/task/1694/

*/
#include <iostream>
#include <vector>
#include <cmath>
#include <limits.h>
#include <memory>

#define INF INT_MAX

using i64 = int64_t;

using namespace std;

struct Edge {
	Edge(size_t n1, size_t n2, i64 fc, i64 bc) : node1(n1), node2(n2), fcap(fc), bcap(bc) {}
	size_t node1;
	size_t node2; 
	i64 fcap;
	i64 bcap;

	size_t to(size_t node) {
		return node==node1 ? node2 : node1;
	}

	void augment(size_t node, i64 flow) {
		if (forward(to(node))) {
			fcap -= flow;
			bcap += flow;
		} else {
			fcap += flow;
			bcap -= flow;
		}
		
	}

	bool forward(size_t node) {
		return node == node2;
	}

	i64 capacity(size_t node) {
		return forward(to(node)) ? fcap : bcap;
	}
};

i64 threshold = 0;
size_t source = 0;
size_t n, m;
vector<vector<shared_ptr<Edge>>> graph;
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

i64 DFSlist(size_t node, i64 flow) {
	if (node == index(n)) return flow;
	if (visited[node]) return 0;
	visited[node] = true;

	for (auto edge : graph[node]) {
		auto cap = edge->capacity(node);
		if (scalingCondition(cap)){
			i64 f = DFSlist(edge->to(node), min(flow, cap));
			if (f > 0) {
				edge->augment(node, f);
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
			flow = DFSlist(source, INF);
			maxflow+=flow;
		} while(flow!=0);
		threshold /= 2;
	}
	return maxflow;
}

//naive dfs without scaling condition
i64 solveNaive() {
	threshold = 0;
	i64 maxflow = 0;
	i64 flow = 0;
	do {
		falsify();
		flow = DFSlist(source, INF);
		maxflow+=flow;
	} while(flow!=0);
	return maxflow;
}

void allocate(){
	graph.resize(n);
}

void construct(size_t a, size_t b, i64 c){
	auto re = make_shared<Edge>(Edge{index(a), index(b), c, 0u});
	graph[index(a)].push_back(re);
	graph[index(b)].push_back(re);
}

void solve(size_t flag) {
	switch(flag) {
		case 0:
			cout << solveNaive();
			break;
		case 1:
			cout << solveScaling();
			break;
		case 2:
			cout << solveEdmondKarp(); 
			break;
		default:
			cout << "Unknown algorithm\n";
			break;
	}
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
	solve(1);

	return 0;
}