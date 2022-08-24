/*
You are given a map of a labyrinth, and your task is to find a path from start to end.
You can walk left, right, up and down.
 
INPUT:
The first input line has two integers n and m: the height and width of the map.

Then there are n lines of m characters describing the labyrinth.
Each character is . (floor), # (wall), A (start), or B (end).
There is exactly one A and one B in the input.
 
OUTPUT:

First print "YES", if there is a path, and "NO" otherwise.

If there is a path, print the length of the shortest such path
and its description as a string consisting of characters L (left), R (right), U (up), and D (down).
You can print any valid solution.
 
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
YES
9
LDDRRRRRU

SOLUTION: 

Use Dijkstra algorithm to find the shortest path from A to B if such exists. 
If the path exists, the cell B contains the length of minimal shortest path from A to B.
Then recostruct the path, by starting from B and always selecting the next cell 
with distance that is less than current distancy by 1, unless you arrive back to A.

VERIFY HERE:

https://cses.fi/problemset/task/1193/

*/

#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <string>
#include <tuple>
#include <stack>
#include <map>
#include <queue>
#include <limits>
#include <cmath>

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

inline bool CheckBounds(const size_t size) {
    return (size < 1 || size > 1000);
}

inline bool CheckInput(const char cell) {
    return (cell != '.' && cell != '#' && cell != 'A' && cell != 'B');
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
    INF(n * m + 1),
    adjacentEdges(n * m),
    visitedNodes(n * m),
    distances(n * m)
    {
        if (CheckBounds(n) || CheckBounds(m))
            throw invalid_argument("Incorrect dimensions!");
    }

    void Init() {
    	for(int i = 0; i < height; i++) {
    		for(int j = 0; j < width; j++) {
                    char cell;
                    READ(cell);

                    AssignCellValue(cell, i, j);
            }
    	}
    }

    void SearchShortestPath() {
        InitializeDistances();

        SetDistance(
            startingNode.second,
            startingNode.first,
            0
        );

        PutNodeToPriorityQueue(
            0,
            {
                startingNode.first,
                startingNode.second
            }
        );

        FindShortestPathWithDijkstraAlgorithm();
    }

    void DisplayGrid() const {
    	for(int i = 0; i < height; i++) {
    		for(int j = 0; j < width; j++) {
    			PrintOut(distances[LinearIndex(i, j)], " ");
    		}
    		PrintOut("\n");
    	}
    }

    void ReconstructShortestPath() {
        int x = endingNode.first;
        int y = endingNode.second;

        map<int, char> directions({
            {0, 'R'},
            {1, 'L'},
            {2, 'D'},
            {3, 'U'}
        });

        while(StartingNodeIsNotReached(y, x)) {
            const auto neighbourNodes = ComputeNeighbouringNodes(y, x);

            for (int i = 0; i < 4; i++) {

                int x0 = neighbourNodes[i].first;
                int y0 = neighbourNodes[i].second;

                if (CellIsWall(y0, x0)) continue;

                bool thisIsNextOptimalStep = (distances[LinearIndex(y0, x0)] == distances[LinearIndex(y, x)] - 1);

                if (thisIsNextOptimalStep) {

                    path.push(directions[i]);
                    x = x0;
                    y = y0;
 
                    break;
                }

            }
        }
    }

    void Check() {
        if (GetDistance(endingNode.second, endingNode.first) != INF) {
            PrintOut("YES", "\n");

            PrintOut(
                GetDistance(endingNode.second, endingNode.first),
                "\n"
            );

            ReconstructShortestPath();

            ShowPath();
        } else {
            PrintOut("NO");
        }
    }

private:
    int height;
    int width;
    size_t size;
    const int INF;
    static const int NONREACHABLE = -1;

    BitVector adjacentEdges;
    BitVector visitedNodes;
    vector<int> distances;
    priority_queue<pair<int, pair<int, int>>> adjacentDistances;

    pair<int, int> startingNode;
    pair<int, int> endingNode;

    stack<char> path;

    inline size_t LinearIndex(const int y, const int x) const {
        return x + y * width;
    }

    void AssignCellValue(const char cell, const int y, const int x) {
        switch(cell) {
            case '.':
                MarkFreeSpaceOnTheMap(y, x);
                break;
            case 'A':
                MarkFreeSpaceOnTheMap(y, x);
                startingNode = {x, y};
                break;
            case 'B':
                MarkFreeSpaceOnTheMap(y, x);
                endingNode = {x, y};
                break;
            case '#':
                break;
            default:
                throw invalid_argument("Incorrect input!");
        }
    }

    inline void MarkFreeSpaceOnTheMap(const int y, const int x) {
        adjacentEdges.SetBit(LinearIndex(y, x));
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

    inline const array<pair<int, int>, 4> ComputeNeighbouringNodes(const int y, const int x) const {
        array<pair<int, int>, 4> neighbourNodes = {
                {
                    {
                        ComputeMinimumHorizontalLeftBound(x),
                        y
                    },

                    {
                        ComputeMaximumHorizontalRightBound(x),
                        y
                    },

                    {
                        x,
                        ComputeMaximumVerticalUpperBound(y)
                    },

                    {
                        x,
                        ComputeMinimumVerticalLowerBound(y)
                    }
                }
            };

        return neighbourNodes;
    }

    inline int ComputeMinimumHorizontalLeftBound(const int x) const {
        return max(x - 1, 0);
    }

    inline int ComputeMaximumHorizontalRightBound(const int x) const {
        return min(x + 1, width - 1);
    }

    inline int ComputeMaximumVerticalUpperBound(const int y) const {
        return max(y - 1, 0);
    }

    inline int ComputeMinimumVerticalLowerBound(const int y) const {
        return min(y + 1, height - 1);
    }

    void InitializeDistances() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (CellIsWall(i, j)){
                    SetDistance(i, j, NONREACHABLE);
                } else {
                    SetDistance(i, j, INF);
                }
            }
        }
    }

    void FindShortestPathWithDijkstraAlgorithm() {
        while (!adjacentDistances.empty()) {
            auto currentNode = adjacentDistances.top();
            adjacentDistances.pop();

            auto x = currentNode.second.first;
            auto y = currentNode.second.second;

            if (NodeHasBeenVisited(y, x)) continue;
            VisitNode(y, x);

            const auto neighbourNodes = ComputeNeighbouringNodes(y, x);

            for (const auto& [x0, y0] : neighbourNodes) {

                if (CellIsWall(y0, x0)) continue;
                if (GetDistance(y, x) + 1 < GetDistance(y0, x0)) {

                    auto newDistance = GetDistance(y, x) + 1;
                    SetDistance(y0, x0, newDistance);

                    PutNodeToPriorityQueue(
                        -GetDistance(y0, x0),
                        {x0, y0}
                    );
                    
                }
            }
        }
    }

    inline void PutNodeToPriorityQueue(int distance, pair<int, int> node) {
        adjacentDistances.push(
            {
                distance,
                node
            }
        );
    }

    inline int GetDistance(const int y, const int x) const {
        return distances[LinearIndex(y, x)];
    }

    inline void SetDistance(const int y, const int x, int value) {
        distances[LinearIndex(y, x)] = value;
    }

    inline bool StartingNodeIsNotReached(const int y, const int x) {
        return x != startingNode.first || y != startingNode.second;
    }

    void ShowPath() {
        while(!path.empty()){
            auto direction = path.top();
            path.pop();
            PrintOut(direction);
        }
    }
};

void run() {
    size_t n, m;
    READ(n);
    READ(m);

    Graph Grid(n, m);

    Grid.Init();
    Grid.SearchShortestPath();
    Grid.Check();
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