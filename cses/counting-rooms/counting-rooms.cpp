/*
You are given a map of a building, and your task is to count the number of its rooms.
The size of the map is n×m squares, and each square is either floor or wall.
You can walk left, right, up, and down through the floor squares.
 
INPUT:
The first input line has two integers n and m: the height and width of the map.

Then there are n lines of m characters describing the map. Each character is either . (floor) or # (wall).
 
OUPUT:
Print one integer: the number of rooms.
 
CONSTRAINTS:
1 <= n,m  <= 1000
 
VERIFY:

*/

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <cmath>

using namespace std;

template <typename T>
void PrintOut(T value, string const& delimeter = "") {
	cout << value << delimeter;
}

struct BitVector {
public:
    explicit BitVector(const int graphSize) :
    bitvector(ComputeSizeOfBitvector(graphSize))
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

    inline int ComputeSizeOfBitvector(const int graphSize) const {
        return (graphSize + DIV - 1) / DIV;
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
	explicit Graph(const int n, const int m) : 
	height(n),
	width(m),
	size(n * m),
	adjacentEdges(n * m),
	visitedNodes(n * m)
	{}

	inline void Init() {
    	for(int i = 0; i < height; i++) {
    		for(int j = 0; j < width; j++) {
    			char cell; 
    			cin >> cell;

    			if (cell == '.')
    				MarkFreeSpaceOnTheMap(i, j);
    		}
    	}
    }

    inline size_t NodeHasBeenVisited(const int y, const int x) const {
    	return visitedNodes.GetBit(LinearIndex(y, x));
    }

    inline size_t CellIsWall(const int y, const int x) const {
    	return !adjacentEdges.GetBit(LinearIndex(y, x));
    }

    inline void VisitNode(const int y, const int x) {
    	visitedNodes.SetBit(LinearIndex(y, x));;
    }

    inline void MarkFreeSpaceOnTheMap(const int y, const int x) {
    	adjacentEdges.SetBit(LinearIndex(y, x));
    }

    inline void CountNode() {
    	counter++;
    }

    inline void CountConnectedComponent() {
    	connectedComponents++;
    }

    inline void ReleaseCounter() {
    	counter = 0;
    }

    inline void DepthFirstSearch(const int y, const int x) {
    	if (NodeHasBeenVisited(y, x) || CellIsWall(y, x)) return;
    	VisitNode(y, x);
    	CountNode();

    	array<pair<short, short>, 4> neighbourNodes = {
    		{
    			{max(x - 1, 0), y},
    			{min(x + 1, width), y},
    			{x, max(y - 1, 0)},
    			{x, min(y + 1, height)}
    		}
    	};

    	for (const auto& [x0, y0] : neighbourNodes) {
    		DepthFirstSearch(y0, x0);
    	}
    }


    inline void ComputeConnectedComponents() {
    	for(int i = 0; i < height; i++) {
    		for(int j = 0; j < width; j++) {
    			DepthFirstSearch(i, j);

    			if (counter > 0)
    				CountConnectedComponent();
    			ReleaseCounter();
    		}
    	}
    }

    inline void DisplayGrid() const {
    	for(int i = 0; i < height; i++) {
    		for(int j = 0; j < width; j++) {
    			PrintOut(adjacentEdges.GetBit(LinearIndex(i, j)), " ");
    		}
    		PrintOut("\n");
    	}
    }

    inline void DisplayConnectedComponents() const {
    	PrintOut(connectedComponents);
    }

private:
	int height;
	int width;
	size_t size;

	BitVector adjacentEdges;
	BitVector visitedNodes;

	int counter = 0;
	int connectedComponents = 0;

	inline size_t LinearIndex(const int y, const int x) const {
		return x + y * width;
	}
};

int main() {
	size_t n, m; 
	cin >> n >> m;

	Graph Grid(n, m);

	Grid.Init();
	Grid.ComputeConnectedComponents();
	Grid.DisplayConnectedComponents();

	return 0;
}