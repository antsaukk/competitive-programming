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

EXAMPLE:

Input:
5 8
########
#..#...#
####.#.#
#..#...#
########

Output:
3

SOLUTION: 
Observe that map with the rooms can be encoded as graph with several connected components. 
Then, we count all connected components: for every cell that is not the wall, 
start Depth-First search and mark all the cells that are part of the room (nodes of the connected component).
For fun, we encode the graph as a bit map with set bit being the node.

VERIFY:
https://cses.fi/problemset/task/1192/
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

bool CheckBounds(const size_t size) {
    return (size < 1 || size > 1000);
}

bool CheckInput(const char cell) {
    return (cell != '.' && cell != '#');
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
    explicit Graph(const int n, const int m) : 
    height(n),
    width(m),
    size(n * m),
    adjacentEdges(n * m),
    visitedNodes(n * m)
    {}

    void Init() {
    	for(int i = 0; i < height; i++) {
    		for(int j = 0; j < width; j++) {
                    char cell;
                    cin >> cell;

                    if (CheckInput(cell)) {
                        throw invalid_argument("Incorrect input!");
                    }

                    if (cell == '.') {
                        MarkFreeSpaceOnTheMap(i, j);
                    }
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

    inline short ComputeMinimumHorizontalLeftBound(const short x) const {
        return max(x - 1, 0);
    }

    inline short ComputeMaximumHorizontalRightBound(const short x) const {
        return min(x + 1, width - 1);
    }

    inline short ComputeMaximumVerticalUpperBound(const short y) const {
        return max(y - 1, 0);
    }

    inline short ComputeMinimumVerticalLowerBound(const short y) const {
        return min(y + 1, height - 1);
    }

    inline const auto ComputeNeighbouringNodes(const short y, const short x) const {

        array<pair<short, short>, 4> neighbourNodes = {

            {
                {ComputeMinimumHorizontalLeftBound(x), y},

                {ComputeMaximumHorizontalRightBound(x), y},

                {x, ComputeMaximumVerticalUpperBound(y)},

                {x, ComputeMinimumVerticalLowerBound(y)}
            }

        };

        return neighbourNodes;
    }

    void DepthFirstSearch(const int y, const int x) {
        if (NodeHasBeenVisited(y, x) || CellIsWall(y, x)) return;
    	VisitNode(y, x);
    	CountNode();

        const auto neighbourNodes = ComputeNeighbouringNodes(y, x);        

    	for (const auto& [x0, y0] : neighbourNodes) {
    		DepthFirstSearch(y0, x0);
    	}
    }


    void ComputeConnectedComponents() {
    	for(int i = 0; i < height; i++) {
    		for(int j = 0; j < width; j++) {
                    DepthFirstSearch(i, j);

                    if (counter > 0) {
                        CountConnectedComponent();
                        ReleaseCounter();
                    }
            }
    	}
    }

    void DisplayGrid() const {
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

    size_t counter = 0;
    size_t connectedComponents = 0;

    inline size_t LinearIndex(const int y, const int x) const {
        return x + y * width;
    }
};

void run() {
    size_t n, m; 
    cin >> n >> m;

    if (CheckBounds(n) || CheckBounds(m)) {
        throw invalid_argument("Incorrect dimensions!");
    }

    Graph Grid(n, m);

    Grid.Init();
    Grid.ComputeConnectedComponents();
    Grid.DisplayConnectedComponents();
}

int main() {
    try {
        run();
    } catch (const invalid_argument& exception) {
        cerr << exception.what() << "\n";
        return -1;
    }

    return 0;
}