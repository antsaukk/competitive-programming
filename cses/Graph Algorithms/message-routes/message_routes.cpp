/*
Syrjälä's network has n
computers and m connections.
Your task is to find out if Uolevi can send a message to Maija, and if it is possible,
what is the minimum number of computers on such a route.

INPUT:
The first input line has two integers n and m: the number of computers and connections.
The computers are numbered 1,2,…,n. Uolevi's computer is 1 and Maija's computer is n.

Then, there are m lines describing the connections.
Each line has two integers a and b: there is a connection between those computers.

Every connection is between two different computers, and there is at most one connection between any two computers.

OUTPUT:
If it is possible to send a message, first print k: the minimum number of computers on a valid route.
After this, print an example of such a route. You can print any valid solution.

If there are no routes, print "IMPOSSIBLE".
 
CONSTRAINTS:

2 <= n <= 10^5
1 <= m <= 2*10^5
1 <= a,b <= n

EXAMPLE:

Input:
5 5
1 2
1 3
1 4
2 3
5 4

Output:
3
1 4 5

VERIFY HERE:
https://cses.fi/problemset/task/1667/

*/

#include <iostream>
#include <vector>
#include <queue>
#include <array>
#include <string>
#include <cmath>

using namespace std;

#define READ(x) (cin >> (x))

template <typename T> 
ostream& operator<<(ostream& os, const vector<T>& v) 
{ 
    for (size_t i = 0; i < v.size(); ++i) { 
        os << v[i]; 
        if (i != v.size() - 1) 
            os << " "; 
    }
    return os; 
}

template <typename T>
void PrintOut(T value, string const& delimeter = "") {
    cout << value << delimeter;
}

const size_t indexify(size_t ord) { return ord-1; }

class Graph {
public:
    explicit Graph(size_t n) : 
    edges_(n)
    {}

    void addEdge(const size_t tail, const size_t head) {
        edges_[tail].push_back(head);
        edges_[head].push_back(tail);
    }

    inline const vector<size_t>& getEdges(const size_t index) const { return edges_[index]; }

    inline const size_t getGraphSize() const                        { return edges_.size(); }

private:
    vector<vector<size_t>> edges_;
};

struct BFSUtils {
    explicit BFSUtils(size_t n) :
    visited_(n),
    distance_(n) {}


    vector<bool> visited_;
    vector<uint> distance_;
    queue<size_t> node_queue_; 
};

void BFS(const Graph& g, BFSUtils& bfs_strct) {
    bfs_strct.visited_[0] = true;
    bfs_strct.distance_[0] = 0;
    bfs_strct.node_queue_.push(0);

    while (!bfs_strct.node_queue_.empty()) {
        auto node = bfs_strct.node_queue_.front();
        bfs_strct.node_queue_.pop();

        for (const auto neighbour : g.getEdges(node)) {
            if (bfs_strct.visited_[neighbour]) continue;

            bfs_strct.visited_[neighbour] = true;
            bfs_strct.distance_[neighbour] = bfs_strct.distance_[node] + 1;
            bfs_strct.node_queue_.push(neighbour);
        }
    }
}

void traversePath(const Graph& g, BFSUtils& bfs_strct) {
    auto dist = bfs_strct.distance_[indexify(g.getGraphSize())];
    vector<size_t> path(dist+1);
    size_t current_node = indexify(g.getGraphSize());
    path[dist] = current_node+1;

    while (dist > 0) {
        for (const auto neigh : g.getEdges(current_node)) {
            if (bfs_strct.distance_[neigh] == dist - 1) {
                path[--dist] = neigh+1;
                current_node = neigh;
                break;
            }
        }
    }

    PrintOut(path);
}

void solve(Graph& g) {
    BFSUtils bfs_strct(g.getGraphSize());

    BFS(g, bfs_strct);

    if (bfs_strct.distance_[indexify(g.getGraphSize())]) {
        PrintOut(bfs_strct.distance_[indexify(g.getGraphSize())] + 1, "\n");

        traversePath(g, bfs_strct);

    } else {
        PrintOut("IMPOSSIBLE");
    }
}

void run() {
    size_t n, m; 
    READ(n); READ(m);

    Graph g(n);
    for (size_t i = 0; i < m; i++) {
        size_t a, b;
        READ(a); READ(b);

        g.addEdge(indexify(a), indexify(b));
    }

    solve(g);

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