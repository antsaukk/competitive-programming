/*
Byteland has n cities, and m roads between them.
The goal is to construct new roads so that there is a route between any two cities.

Your task is to find out the minimum number of roads required, and also determine which roads should be built.
 
INPUT:
The first input line has two integers n and m: the number of cities and roads. The cities are numbered 1,2,…,n.

After that, there are m lines describing the roads. Each line has two integers a and b: there is a road between those cities.

A road always connects two different cities, and there is at most one road between any two cities.

OUTPUT:

First print an integer k: the number of required roads.

Then, print k lines that describe the new roads. You can print any valid solution.
 
CONSTRAINTS:
1 <= n <= 10^5
1 <= m <= 2*10^5
1 <= a,b <= n

EXAMPLE:

Input:
4 2
1 2
3 4

Output:
1
2 3

SOLUTION: 

Represent map with the cities as graph with connected components. 
Use Depth-First Search to find all connected components and record the edges
required to connect two components.

VERIFY HERE:

https://cses.fi/problemset/task/1666/

*/

#include <iostream>
#include <vector>

#define READ(x) (cin >> (x))

using namespace std;

inline void desyncio() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

template <typename T>
inline void PrintOut(T value, string const& delimeter = "") {
	cout << value << delimeter;
}

template <typename T> 
inline T Indexify(T naturalOrdering) {
	return naturalOrdering - 1;
}

inline bool CheckBounds(const size_t parameter, const size_t upperBound) {
    return (parameter < 1 || parameter > upperBound);
}

struct BitVector {
public:
    explicit BitVector(const int sequenceLength) :
    bitvector(ComputeSizeOfBitvector(sequenceLength))
    {}

    inline void SetBit(const int position) {
        const int bitix  = position / DIV;
        const int shift  = ComputeShift(position);
        bitvector[bitix] |= (ONE << shift);
    }

    inline size_t GetBit(const int position) const {
        const int bitix = position / DIV;
        const int shift = ComputeShift(position);
        return ((bitvector[bitix] & (ONE << shift)) >> shift);
    }

    inline int ComputeSizeOfBitvector(const int sequenceLength) const {
        return (sequenceLength + DIV - 1) / DIV;
    }

    inline uint64_t GetBits(const int position) const {
        return bitvector[position];
    }

private:
    static const long long DIV = 64L;
    static const long long ONE = 1L;

    inline int ComputeShift(const int position) const {
        return DIV - position % DIV - 1;
    }

    vector<uint64_t> bitvector;
};

class Graph {
public:
	explicit Graph(const int nodes, const int edges) :
	numberOfNodes(nodes),
	numberOfEdges(edges),
	adjacentNodes(nodes),
	visitedNodes(nodes) 
	{
		if (CheckBounds(nodes, 100'000) || CheckBounds(edges, 200'000))
			throw invalid_argument("Incorrect graph-parameters!");
	}

	void Init() {
		for (int i = 0; i < numberOfEdges; i++) {
			int tailNode, headNode;

			READ(tailNode);
			READ(headNode);

			AddEdge(tailNode, headNode);
		}
	}

	void ConnectComponents() {
		DepthFirstSearch(0);

		for (int node = 1; node < numberOfNodes; node++) {
			if (!NodeHasBeenVisited(node)) {
				DepthFirstSearch(node);

				addedEdges.push_back(
					{node, node+1}
				);
			}
		}
	}

	void DisplayGraph() const {
		for (int i = 0; i < numberOfNodes; i++) {
			for (size_t j = 0; j < adjacentNodes[i].size(); j++) {
				PrintOut("Node ");
				PrintOut(i, " ");
				PrintOut("has the following edges:\n");
				PrintOut(adjacentNodes[i][j], "\n");
			}
		}
	}

	void ShowAddedEdges() const {
		PrintOut(addedEdges.size(), "\n");

		for (const auto& [tail, head]: addedEdges) {
			PrintOut(tail, " ");
			PrintOut(head, "\n");
		}
	}

private:
	const int numberOfNodes;
	const int numberOfEdges;

	vector<vector<int>> adjacentNodes;
	BitVector visitedNodes;

	vector<pair<int, int>> addedEdges;

	inline void AddEdge(const int tailNode, const int headNode) {
		if (CheckBounds(tailNode, numberOfNodes) || CheckBounds(headNode, numberOfNodes))
			throw invalid_argument("Edge must connect only existing nodes!");

		int indexedTailNode = Indexify(tailNode);
		int indexedHeadNode = Indexify(headNode);

		adjacentNodes[indexedTailNode].push_back(indexedHeadNode);
		adjacentNodes[indexedHeadNode].push_back(indexedTailNode);
	}

	void DepthFirstSearch(const int node) {
		if (NodeHasBeenVisited(node)) return;
		VisitNode(node);

		for (const auto& neighbouringNode : adjacentNodes[node]) {
			DepthFirstSearch(neighbouringNode);
		}
	}

	inline size_t NodeHasBeenVisited(const int node) const {
        return visitedNodes.GetBit(node);
    }

    inline void VisitNode(const int node) {
        visitedNodes.SetBit(node);
    }
};

void run() {
	size_t n, m; 

	READ(n);
	READ(m);

	Graph Map(n, m);

	Map.Init();
	//Map.DisplayGraph();
	Map.ConnectComponents();
	Map.ShowAddedEdges();

}

int main() {
	desyncio();

	try {
		run();
	} catch (const invalid_argument& exception) {
		cerr << exception.what() << "\n";
		return -1;
	}

	return 0;
}