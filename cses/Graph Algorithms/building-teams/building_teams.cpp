/*
There are n pupils in Uolevi's class, and m
friendships between them.
Your task is to divide the pupils into two teams in such a way that no two pupils in a team are friends.
You can freely choose the sizes of the teams.

INPUT:
The first input line has two integers n and m: the number of pupils and friendships. The pupils are numbered 1,2,…,n
Then, there are m lines describing the friendships. Each line has two integers a and b: pupils a and b are friends.

Every friendship is between two different pupils. You can assume that there is at most one friendship between any two pupils.

OUTPUT:
Print an example of how to build the teams. For each pupil, print "1" or "2" depending on to which team
the pupil will be assigned. You can print any valid team.
If there are no solutions, print "IMPOSSIBLE".
 
CONSTRAINTS:

2 <= n <= 10^5
1 <= m <= 2*10^5
1 <= a,b <= n

EXAMPLE:


Input:
5 3
1 2
1 3
4 5

Output:
1 2 2 1 2

VERIFY HERE:
https://cses.fi/problemset/task/1668/

*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <cmath>

using namespace std;

#define READ(x) (cin >> (x))

template <typename T> 
ostream& operator<<(ostream& os, const vector<T>& v) { 
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

const size_t indexify(size_t ord) { return ord - 1; }

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

struct Utils {
    explicit Utils(size_t n) :
    visited_(n),
    teams_distribution_(n) {}

    vector<bool> visited_;
    vector<size_t> teams_distribution_;
    unordered_set<size_t> team_one_;
    unordered_set<size_t> team_two_;
};

void DFS(Graph& g, Utils& dfs_str, size_t node) {
    if (dfs_str.visited_[node]) return;

    dfs_str.visited_[node] = true;

    size_t has_neighbours = 0;
    for (const auto neighbour : g.getEdges(node)) {
        has_neighbours++;

        if (dfs_str.team_one_.count(node)) {
            dfs_str.teams_distribution_[neighbour] = 2;
            dfs_str.team_two_.insert(neighbour);
        } else {
            dfs_str.teams_distribution_[neighbour] = 1;
            dfs_str.team_one_.insert(neighbour);
        }

        DFS(g, dfs_str, neighbour);
    }

    if (!has_neighbours) {
        dfs_str.team_one_.insert(node);
        dfs_str.teams_distribution_[node] = 1;
    } 
}

bool checkIntersection(Utils& dfs_str) {
    for (const auto node : dfs_str.team_one_) {
        if (dfs_str.team_two_.count(node))
            return true;
    }

    return false;
}

void solve(Graph& g) {
    Utils dfs_str(g.getGraphSize());
    dfs_str.teams_distribution_[0] = 1;
    dfs_str.team_one_.insert(0);

    for (size_t node = 0; node < g.getGraphSize(); node++) {
        DFS(g, dfs_str, node);
    }

    if (!checkIntersection(dfs_str)) {
        PrintOut(dfs_str.teams_distribution_);
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